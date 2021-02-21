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



#ifndef TA_DRIVER_H
#define TA_DRIVER_H



#include "common.h"
#include "debug.h"
#include "filter_engine.h"



/*
 * The entry point of the driver. Handles resource acquisition and driver setup.
 */
NTSTATUS NTAPI DriverEntry(_In_ PDRIVER_OBJECT pDriverObject, _In_ PUNICODE_STRING pRegistryPath);



/*
 * The exit point of the driver. Handles resource release.
 */
VOID NTAPI DriverExit(_In_ PDRIVER_OBJECT pDriverObject);



#endif // !TA_DRIVER_H