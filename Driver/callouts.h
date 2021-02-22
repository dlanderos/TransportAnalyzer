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



#ifndef TA_CALLOUTS_H
#define TA_CALLOUTS_H



#include "common.h"
#include "debug.h"
#include "tcp_utils.h"



// a0c5675d-8c23-462f-8353-1a913b6fc0af
DEFINE_GUID(TA_CALLOUT_INBOUND_GUID, 0xa0c5675dL, 0x8c23, 0x462f, 0x83, 0x53, 0x1a, 0x91, 0x3b, 0x6f, 0xc0, 0xaf);
#define TA_CALLOUT_INBOUND_NAME L"ta_callout_inbound"
#define TA_CALLOUT_INBOUND_DESCRIPTION L"Callout used for inspecting inbound TCP packets"
#define TA_CALLOUT_INBOUND_POOL_TAG (UINT32) 'IAT'



// ee94ec3d-04d7-44d0-b765-3841adfa2f38
DEFINE_GUID(TA_CALLOUT_OUTBOUND_GUID, 0xee94ec3dL, 0x04d7, 0x44d0, 0xb7, 0x65, 0x38, 0x41, 0xad, 0xfa, 0x2f, 0x38);
#define TA_CALLOUT_OUTBOUND_NAME L"ta_callout_outbound"
#define TA_CALLOUT_OUTBOUND_DESCRIPTION L"Callout used for inspecting outbound TCP packets"
#define TA_CALLOUT_OUTBOUND_POOL_TAG (UINT32) 'OAT'



/*
 * Creates the inbound callout with the provided filter engine handle and device object pointer.
 */
NTSTATUS taCreateCalloutInbound(_In_ HANDLE engineHandle, _In_ PDEVICE_OBJECT pDeviceObject);



/*
 * Deletes the inbound callout with the provided filter engine handle and device object pointer.
 */
NTSTATUS taDeleteCalloutInbound(_In_ HANDLE engineHandle, _In_ PDEVICE_OBJECT pDeviceObject);



/*
 * Handles each classification action on the inbound side of the transport layer. This function will do the actual
 * analyzation of the TCP packets. See <https://docs.microsoft.com/en-us/windows-hardware/drivers/network/processing-classify-callouts>
 * for more information.
 */
VOID NTAPI taClassifyInbound(
	_In_ const FWPS_INCOMING_VALUES* pInFixedValues,
	_In_ const FWPS_INCOMING_METADATA_VALUES* pInMetaValues,
	_Inout_opt_ void* pLayerData,
	_In_opt_ const void* pClassifyContext,
	_In_ const FWPS_FILTER* pFilter, _In_ UINT64 flowContext, _Inout_ FWPS_CLASSIFY_OUT* pClassifyOut
);



/*
 * Handles events that are in association with the inbound callout.
 * See <https://docs.microsoft.com/en-us/windows-hardware/drivers/network/processing-notify-callouts> for more information.
 */
NTSTATUS NTAPI taNotifyInbound(
	_In_ FWPS_CALLOUT_NOTIFY_TYPE notifyType,
	_In_ const GUID* pFilterKey,
	_Inout_ FWPS_FILTER* pFilter
);



/*
 * Handles cleanup when the data flow has been stopped on the inbound callout.
 * See <https://docs.microsoft.com/en-us/windows-hardware/drivers/network/processing-flow-delete-callouts> for more information.
 */
VOID NTAPI taFlowDeleteInbound(
	_In_ UINT16 layerId,
	_In_ UINT32 calloutId,
	_In_ UINT64 flowContext
);



/*
 * Creates the outbound callout with the provided filter engine handle and device object pointer.
 */
NTSTATUS taCreateCalloutOutbound(_In_ HANDLE engineHandle, _In_ PDEVICE_OBJECT pDeviceObject);



/*
 * Deletes the outbound callout with the provided filter engine handle and device object pointer.
 */
NTSTATUS taDeleteCalloutOutbound(_In_ HANDLE engineHandle, _In_ PDEVICE_OBJECT pDeviceObject);



/*
 * Handles each classification action on the outbound side of the transport layer. This function will do the actual
 * analyzation of the TCP packets. See <https://docs.microsoft.com/en-us/windows-hardware/drivers/network/processing-classify-callouts>
 * for more information.
 */
VOID NTAPI taClassifyOutbound(
	_In_ const FWPS_INCOMING_VALUES* pInFixedValues,
	_In_ const FWPS_INCOMING_METADATA_VALUES* pInMetaValues,
	_Inout_opt_ void* pLayerData,
	_In_opt_ const void* pClassifyContext,
	_In_ const FWPS_FILTER* pFilter, _In_ UINT64 flowContext, _Inout_ FWPS_CLASSIFY_OUT* pClassifyOut
);



/*
 * Handles events that are in association with the outbound callout.
 * See <https://docs.microsoft.com/en-us/windows-hardware/drivers/network/processing-notify-callouts> for more information.
 */
NTSTATUS NTAPI taNotifyOutbound(
	_In_ FWPS_CALLOUT_NOTIFY_TYPE notifyType,
	_In_ const GUID* pFilterKey,
	_Inout_ FWPS_FILTER* pFilter
);



/*
 * Handles cleanup when the data flow has been stopped on the outbound callout.
 * See <https://docs.microsoft.com/en-us/windows-hardware/drivers/network/processing-flow-delete-callouts> for more information.
 */
VOID NTAPI taFlowDeleteOutbound(
	_In_ UINT16 layerId,
	_In_ UINT32 calloutId,
	_In_ UINT64 flowContext
);



#endif // !TA_CALLOUTS_H