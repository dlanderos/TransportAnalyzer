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



#ifndef TA_LAYERS_H
#define TA_LAYERS_H



#include "common.h"
#include "debug.h"



// 2e1c2363-fdf0-43f8-be33-98902cf2587d
DEFINE_GUID(TA_SUBLAYER_GUID, 0x2e1c2363L, 0xfdf0, 0x43f8, 0xbe, 0x33, 0x98, 0x90, 0x2c, 0xf2, 0x58, 0x7d);
#define TA_SUBLAYER_NAME L"ta_sublayer"
#define TA_SUBLAYER_DESCRIPTION L"Sublayer used for TCP packet processing"



/*
 * Creates the sublayer with the provided filter engine handle
 */
NTSTATUS taCreateSublayer(_In_ HANDLE engineHandle);



/*
 * Deletes the sublayer with the provided filter engine handle
 */
NTSTATUS taDeleteSublayer(_In_ HANDLE engineHandle);



#endif // !TA_LAYERS_H