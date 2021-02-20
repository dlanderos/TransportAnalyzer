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



#include "sublayers.h"



NTSTATUS taCreateSublayer(_In_ HANDLE engineHandle) {
	FWPM_SUBLAYER sublayer = {
		.subLayerKey = TA_SUBLAYER_GUID,
		.displayData = {
			.name = TA_SUBLAYER_NAME,
			.description = TA_SUBLAYER_DESCRIPTION,
		},
		.flags = 0,
		.weight = 0x0F
	};
	NTSTATUS status = FwpmSubLayerAdd(engineHandle, &sublayer, NULL);
	TA_DEBUG_ONLY_LOG_ERROR_STATUS("failed to add sublayer", status);
	return status;
}



NTSTATUS taDeleteSublayer(_In_ HANDLE engineHandle) {
	NTSTATUS status = FwpmSubLayerDeleteByKey(engineHandle, &TA_SUBLAYER_GUID);
	TA_DEBUG_ONLY_LOG_ERROR_STATUS("failed to delete sublayer", status);
	return status;
}