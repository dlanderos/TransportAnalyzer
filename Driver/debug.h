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



#ifndef TA_DEBUG_H
#define TA_DEBUG_H



#include "common.h"



#ifdef _DEBUG



/*
 * Print formatted message only when debugging
 */
#define TA_DEBUG_ONLY_PRINTF(format, ...) \
	DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, format, __VA_ARGS__);



/*
 * Print message on new line only when debugging
 */
#define TA_DEBUG_ONLY_PRINTLN(message) \
	DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "%s\n", message);



/*
 * Print message only when debugging and only when the status isn't SUCCESS
 */
#define TA_DEBUG_ONLY_LOG_ERROR_STATUS(message, status) \
	if (!NT_SUCCESS(status)) { \
		DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "ERROR: %s CODE: 0x%08x\n", message, status); \
	}



/*
 * Print message only when debugging and only when the status is SUCCESS
 */
#define TA_DEBUG_ONLY_LOG_SUCCESS_STATUS(message, status) \
	if (NT_SUCCESS(status)) { \
		DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "SUCESSS: %s\n", message); \
	}



#else



/*
 * Default to doing nothing when not in debug mode 
 */
#define TA_DEBUG_ONLY_PRINTF(format, ...)



/*
 * Default to doing nothing when not in debug mode
 */
#define TA_DEBUG_ONLY_PRINTLN(message)



/*
 * Default to doing nothing when not in debug mode
 */
#define TA_DEBUG_ONLY_LOG_ERROR_STATUS(message, status)



/*
 * Default to doing nothing when not in debug mode
 */
#define TA_DEBUG_ONLY_LOG_SUCCESS_STATUS(message, status)



#endif



#endif // !TA_DEBUG_H