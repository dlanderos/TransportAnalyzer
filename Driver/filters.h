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



#ifndef TA_FILTERS_H
#define TA_FILTERS_H



#include "common.h"
#include "debug.h"
#include "sublayers.h"
#include "callouts.h"



// f0afae44-0354-4ae9-a877-892ddc179730
DEFINE_GUID(TA_FILTER_INBOUND_GUID, 0xf0afae44L, 0x0354, 0x4ae9, 0xa8, 0x77, 0x89, 0x2d, 0xdc, 0x17, 0x97, 0x30);
#define TA_FILTER_INBOUND_NAME L"ta_filter_inbound"
#define TA_FILTER_INBOUND_DESCRIPTION L"Inbound filter for extracting TCP packets"



/*
 * Creates the inbound filter with the provided engine handle.
 */
NTSTATUS taCreateFilterInbound(_In_ HANDLE engineHandle);



/*
 * Deletes the outbound filter with the provided engine handle.
 */
NTSTATUS taDeleteFilterInbound(_In_ HANDLE engineHandle);



// cfcb45c8-0889-4059-96d8-c9a8c4dd82f3
DEFINE_GUID(TA_FILTER_OUTBOUND_GUID, 0xcfcb45c8L, 0x0889, 0x4059, 0x96, 0xd8, 0xc9, 0xa8, 0xc4, 0xdd, 0x82, 0xf3);
#define TA_FILTER_OUTBOUND_NAME L"ta_filter_outbound"
#define TA_FILTER_OUTBOUND_DESCRIPTION L"Outbound filter for extracting TCP packets"



/*
 * Creates the outbound filter with the provided engine handle.
 */
NTSTATUS taCreateFilterOutbound(_In_ HANDLE engineHandle);



/*
 * Deletes the outbound filter with the provided engine handle.
 */
NTSTATUS taDeleteFilterOutbound(_In_ HANDLE engineHandle);



#endif // !TA_FILTERS_H