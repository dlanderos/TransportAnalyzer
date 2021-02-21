/*
 * TransportAnalyzer: a simple WFP KMD for analyzing incoming and outgoing TCP packets.
 * Copyright (C) 2021 dxboats
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */



#include "filter_engine.h"



HANDLE gEngineSubscribeCallbackHandle;
HANDLE gEngineHandle;



/*
 * This callback is called whenever the filter engine is put into a new state. Listening for the
 * FWPM_SERVICE_RUNNING state so the engine can be accessed.
 */
VOID NTAPI taEngineSubscribeCallback(_Inout_ VOID* context, _In_ FWPM_SERVICE_STATE newState) {
	if (newState == FWPM_SERVICE_RUNNING && !gEngineHandle) {
		taFilterEngineOpen((PDEVICE_OBJECT) context);
	}
}



/*
 * Begin the setup process for the filter engine. In the event the filter engine isn't running,
 * it will setup a hook to listen for when it starts and it can then commit a transaction. If it's
 * already running, the transaction can be begun immediately.
 */
NTSTATUS taFilterEngineBegin(_In_ PDEVICE_OBJECT pDeviceObject) {
	NTSTATUS status = STATUS_SUCCESS;

	status = FwpmBfeStateSubscribeChanges(pDeviceObject, taEngineSubscribeCallback, pDeviceObject, &gEngineSubscribeCallbackHandle);
	TA_DEBUG_ONLY_LOG_ERROR_STATUS("failed to subscribe to filter engine", status);
	if (!NT_SUCCESS(status)) {
		goto finalize;
	}
	FWPM_SERVICE_STATE filterEngineState = FwpmBfeStateGet();
	if (filterEngineState != FWPM_SERVICE_RUNNING) {
		TA_DEBUG_ONLY_PRINTF("filter engine not running STATE: 0x%08x\n", filterEngineState)
		goto finalize;
	}

	status = taFilterEngineOpen(pDeviceObject);

finalize:
	return status;
}



/*
 * Begin and commit the filter engine transaction. Adds the filters, sublayers, and callouts.
 */
NTSTATUS taFilterEngineOpen(_In_ PDEVICE_OBJECT pDeviceObject) {
	NTSTATUS status = STATUS_SUCCESS;
	BOOLEAN transaction = FALSE;
	BOOLEAN registerInboundCallout = FALSE;
	BOOLEAN registerOutboundCallout = FALSE;
	BOOLEAN registerSublayer = FALSE;
	BOOLEAN registerInboundFilter = FALSE;
	BOOLEAN registerOutboundFilter = FALSE;

	FWPM_SESSION engineSession = {
		.flags = FWPM_SESSION_FLAG_DYNAMIC,
	};

	// Attempt to open up the filter engine
	status = FwpmEngineOpen(NULL, RPC_C_AUTHN_WINNT, NULL, &engineSession, &gEngineHandle);
	TA_DEBUG_ONLY_LOG_ERROR_STATUS("failed to open filter engine", status);
	if (!NT_SUCCESS(status)) {
		goto finalize;
	}

	// Attempt to begin filter engine transaction
	status = FwpmTransactionBegin(gEngineHandle, 0);
	TA_DEBUG_ONLY_LOG_ERROR_STATUS("failed to begin filter engine transaction", status);
	if (!NT_SUCCESS(status)) {
		goto finalize;
	}
	transaction = TRUE;

	// Attempt to create inbound callout
	status = taCreateCalloutInbound(gEngineHandle, pDeviceObject);
	if (!NT_SUCCESS(status)) {
		goto finalize;
	}
	registerInboundCallout = TRUE;

	// Attempt to create outbound callout
	status = taCreateCalloutOutbound(gEngineHandle, pDeviceObject);
	if (!NT_SUCCESS(status)) {
		goto finalize;
	}
	registerOutboundCallout = TRUE;

	// Attempt to create a sublayer
	status = taCreateSublayer(gEngineHandle);
	if (!NT_SUCCESS(status)) {
		goto finalize;
	}
	registerSublayer = TRUE;

	// Attempt to create inbound filter
	status = taCreateFilterInbound(gEngineHandle);
	if (!NT_SUCCESS(status)) {
		goto finalize;
	}
	registerInboundFilter = TRUE;

	// Attempt to create outbound filter
	status = taCreateFilterOutbound(gEngineHandle);
	if (!NT_SUCCESS(status)) {
		goto finalize;
	}
	registerOutboundFilter = TRUE;

	// Attempt to commit the transaction
	status = FwpmTransactionCommit(gEngineHandle);
	if (!NT_SUCCESS(status)) {
		TA_DEBUG_ONLY_LOG_ERROR_STATUS("failed to commit filter engine transaction", status);
		goto finalize;
	}
	transaction = FALSE;

finalize:
	// If it wasn't successful, clean up any resources that may have been created
	if (!NT_SUCCESS(status)) {
		if (transaction) {
			FwpmTransactionAbort(gEngineHandle);
		}
		if (registerInboundCallout) {
			taDeleteCalloutInbound(gEngineHandle, pDeviceObject);
		}
		if (registerOutboundCallout) {
			taDeleteCalloutOutbound(gEngineHandle, pDeviceObject);
		}
		if (registerSublayer) {
			taDeleteSublayer(gEngineHandle);
		}
		if (registerInboundFilter) {
			taDeleteFilterInbound(gEngineHandle);
		}
		if (registerOutboundFilter) {
			taDeleteFilterOutbound(gEngineHandle);
		}
	}

	return status;
}



/*
 * Closes the filter engine and frees resources that are no longer needed.
 */
NTSTATUS taFilterEngineClose(_In_ PDEVICE_OBJECT pDeviceObject) {
	NTSTATUS status = STATUS_SUCCESS;

	status = taDeleteFilterOutbound(gEngineHandle);
	if (!NT_SUCCESS(status)) {
		goto finalize;
	}

	status = taDeleteFilterInbound(gEngineHandle);
	if (!NT_SUCCESS(status)) {
		goto finalize;
	}

	status = taDeleteSublayer(gEngineHandle);
	if (!NT_SUCCESS(status)) {
		goto finalize;
	}

	status = taDeleteCalloutOutbound(gEngineHandle, pDeviceObject);
	if (!NT_SUCCESS(status)) {
		goto finalize;
	}

	status = taDeleteCalloutInbound(gEngineHandle, pDeviceObject);
	if (!NT_SUCCESS(status)) {
		goto finalize;
	}

	status = FwpmBfeStateUnsubscribeChanges(gEngineSubscribeCallbackHandle);
	TA_DEBUG_ONLY_LOG_ERROR_STATUS("failed to unsubscribe from filter engine", status);
	if (!NT_SUCCESS(status)) {
		goto finalize;
	}

	status = FwpmEngineClose(gEngineHandle);
	TA_DEBUG_ONLY_LOG_ERROR_STATUS("failed to open filter engine", status);
	if (!NT_SUCCESS(status)) {
		goto finalize;
	}

finalize:
	return status;
}