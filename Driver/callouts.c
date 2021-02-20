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



#include "callouts.h"



UINT32 gCalloutInboundIdentifier;
UINT32 gCalloutOutboundIdentifier;



/*
 * Creates the inbound callout with the provided filter engine handle and device object pointer.
 */
NTSTATUS taCreateCalloutInbound(_In_ HANDLE engineHandle, _In_ PDEVICE_OBJECT pDeviceObject) {
	NTSTATUS status = STATUS_SUCCESS;

	FWPS_CALLOUT calloutRegister = {
		.calloutKey = TA_CALLOUT_INBOUND_GUID,
		.flags = 0,
		.classifyFn = taClassifyInbound,
		.notifyFn = taNotifyInbound,
		.flowDeleteFn = taFlowDeleteInbound,
	};

	status = FwpsCalloutRegister(pDeviceObject, &calloutRegister, &gCalloutInboundIdentifier);
	TA_DEBUG_ONLY_LOG_ERROR_STATUS("failed to register inbound callout", status);
	if (!NT_SUCCESS(status)) {
		return status;
	}

	FWPM_CALLOUT calloutAdd = {
		.calloutKey = TA_CALLOUT_INBOUND_GUID,
		.displayData = {
			.name = TA_CALLOUT_INBOUND_NAME,
			.description = TA_CALLOUT_INBOUND_DESCRIPTION,
		},
		.flags = 0,
		.applicableLayer = FWPM_LAYER_INBOUND_TRANSPORT_V4,
		.calloutId = gCalloutInboundIdentifier,
	};

	status = FwpmCalloutAdd(engineHandle, &calloutAdd, NULL, NULL);
	TA_DEBUG_ONLY_LOG_ERROR_STATUS("failed to add inbound callout to filter engine", status);
	return status;
}



/*
 * Deletes the inbound callout with the provided filter engine handle and device object pointer.
 * Unsure if the callout needs to be both unregistered and deleted?
 */
NTSTATUS taDeleteCalloutInbound(_In_ HANDLE engineHandle, _In_ PDEVICE_OBJECT pDeviceObject) {
	UNREFERENCED_PARAMETER(engineHandle);
	UNREFERENCED_PARAMETER(pDeviceObject);
	NTSTATUS status = STATUS_SUCCESS;
	status = FwpsCalloutUnregisterById(gCalloutInboundIdentifier);
	TA_DEBUG_ONLY_LOG_ERROR_STATUS("failed to unregister inbound callout", status);
	if (!NT_SUCCESS(status)) {
		return status;
	}
	status = FwpmCalloutDeleteByKey(engineHandle, &TA_CALLOUT_INBOUND_GUID);
	TA_DEBUG_ONLY_LOG_ERROR_STATUS("failed to delete inbound callout from filter engine", status);
	return status;
}



/*
 * Always allows the packet through. Will print the packet's payload and TCP header flags.
 */
VOID NTAPI taClassifyInbound(
	_In_ const FWPS_INCOMING_VALUES* pInFixedValues,
	_In_ const FWPS_INCOMING_METADATA_VALUES* pInMetaValues,
	_Inout_opt_ void* pLayerData,
	_In_opt_ const void* pClassifyContext,
	_In_ const FWPS_FILTER* pFilter, _In_ UINT64 flowContext, _Inout_ FWPS_CLASSIFY_OUT* pClassifyOut
) {

}



/*
 * Doesn't do anything. There currently is no need to listen to callout events.
 */
NTSTATUS NTAPI taNotifyInbound(_In_ FWPS_CALLOUT_NOTIFY_TYPE notifyType, _In_ const GUID* pFilterKey, _Inout_ FWPS_FILTER* pFilter) {
	UNREFERENCED_PARAMETER(notifyType);
	UNREFERENCED_PARAMETER(pFilterKey);
	UNREFERENCED_PARAMETER(pFilter);
}



/*
 * Doesn't do anything. There currently aren't any resources that need to be cleaned up once the data is stopped.
 */
VOID NTAPI taFlowDeleteInbound(_In_ UINT16 layerId, _In_ UINT32 calloutId, _In_ UINT64 flowContext) {
	UNREFERENCED_PARAMETER(layerId);
	UNREFERENCED_PARAMETER(calloutId);
	UNREFERENCED_PARAMETER(flowContext);
}



/*
 * Creates the outbound callout with the provided filter engine handle and device object pointer.
 */
NTSTATUS taCreateCalloutOutbound(_In_ HANDLE engineHandle, _In_ PDEVICE_OBJECT pDeviceObject) {
	NTSTATUS status = STATUS_SUCCESS;

	FWPS_CALLOUT calloutRegister = {
		.calloutKey = TA_CALLOUT_OUTBOUND_GUID,
		.flags = 0,
		.classifyFn = taClassifyOutbound,
		.notifyFn = taNotifyOutbound,
		.flowDeleteFn = taFlowDeleteOutbound,
	};

	status = FwpsCalloutRegister(pDeviceObject, &calloutRegister, &gCalloutOutboundIdentifier);
	TA_DEBUG_ONLY_LOG_ERROR_STATUS("failed to register outbound callout", status);
	if (!NT_SUCCESS(status)) {
		return status;
	}

	FWPM_CALLOUT calloutAdd = {
		.calloutKey = TA_CALLOUT_OUTBOUND_GUID,
		.displayData = {
			.name = TA_CALLOUT_OUTBOUND_NAME,
			.description = TA_CALLOUT_OUTBOUND_DESCRIPTION,
		},
		.flags = 0,
		.applicableLayer = FWPM_LAYER_OUTBOUND_TRANSPORT_V4,
		.calloutId = gCalloutOutboundIdentifier,
	};

	status = FwpmCalloutAdd(engineHandle, &calloutAdd, NULL, NULL);
	TA_DEBUG_ONLY_LOG_ERROR_STATUS("failed to add outbound callout to filter engine", status);
	return status;
}



/*
 * Deletes the outbound callout with the provided filter engine handle and device object pointer.
 * Unsure if the callout needs to be both unregistered and deleted?
 */
NTSTATUS taDeleteCalloutOutbound(_In_ HANDLE engineHandle, _In_ PDEVICE_OBJECT pDeviceObject) {
	UNREFERENCED_PARAMETER(engineHandle);
	UNREFERENCED_PARAMETER(pDeviceObject);
	NTSTATUS status = STATUS_SUCCESS;
	status = FwpsCalloutUnregisterById(gCalloutOutboundIdentifier);
	TA_DEBUG_ONLY_LOG_ERROR_STATUS("failed to unregister outbound callout", status);
	if (!NT_SUCCESS(status)) {
		return status;
	}
	status = FwpmCalloutDeleteByKey(engineHandle, &TA_CALLOUT_OUTBOUND_GUID);
	TA_DEBUG_ONLY_LOG_ERROR_STATUS("failed to delete outbound callout from filter engine", status);
	return status;
}



/*
 * Always allows the packet through. Will print the packet's payload and TCP header flags.
 */
VOID NTAPI taClassifyOutbound(
	_In_ const FWPS_INCOMING_VALUES* pInFixedValues,
	_In_ const FWPS_INCOMING_METADATA_VALUES* pInMetaValues,
	_Inout_opt_ void* pLayerData,
	_In_opt_ const void* pClassifyContext,
	_In_ const FWPS_FILTER* pFilter, _In_ UINT64 flowContext, _Inout_ FWPS_CLASSIFY_OUT* pClassifyOut
) {

}



/*
 * Doesn't do anything. There currently is no need to listen to callout events.
 */
NTSTATUS NTAPI taNotifyOutbound(_In_ FWPS_CALLOUT_NOTIFY_TYPE notifyType, _In_ const GUID* pFilterKey, _Inout_ FWPS_FILTER* pFilter) {
	UNREFERENCED_PARAMETER(notifyType);
	UNREFERENCED_PARAMETER(pFilterKey);
	UNREFERENCED_PARAMETER(pFilter);
}



/*
 * Doesn't do anything. There currently aren't any resources that need to be cleaned up once the data is stopped.
 */
VOID NTAPI taFlowDeleteOutbound(_In_ UINT16 layerId, _In_ UINT32 calloutId, _In_ UINT64 flowContext) {
	UNREFERENCED_PARAMETER(layerId);
	UNREFERENCED_PARAMETER(calloutId);
	UNREFERENCED_PARAMETER(flowContext);
}