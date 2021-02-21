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



#include "driver.h"



PDEVICE_OBJECT gDeviceObject;



 /*
  * The entry point of the driver. Handles resource acquisition and driver setup.
  */
NTSTATUS NTAPI DriverEntry(_In_ PDRIVER_OBJECT pDriverObject, _In_ PUNICODE_STRING pRegistryPath) {
	UNREFERENCED_PARAMETER(pRegistryPath);

	// Driver Entry
	TA_DEBUG_ONLY_PRINTLN("Driver ENTRY.");

	NTSTATUS status = STATUS_SUCCESS;
	pDriverObject->DriverUnload = DriverExit;

	// Attempt to create the device
	status = IoCreateDevice(pDriverObject, 0, NULL, FILE_DEVICE_NETWORK, FILE_DEVICE_SECURE_OPEN, FALSE, &gDeviceObject);
	TA_DEBUG_ONLY_LOG_ERROR_STATUS("failed to create device", status);
	if (!NT_SUCCESS(status)) {
		goto finalize;
	}

	// Prepare the filter engine and open if ready. Will commit transactions once the filter engine is running.
	status = taFilterEngineBegin(gDeviceObject);
	if (!NT_SUCCESS(status)) {
		goto finalize;
	}

finalize:
	TA_DEBUG_ONLY_LOG_SUCCESS_STATUS("SUCCESS: Passed with no observable errors.", status);
	return status;
}



/*
 * The exit point of the driver. Handles resource release.
 */
VOID NTAPI DriverExit(_In_ PDRIVER_OBJECT pDriverObject) {
	UNREFERENCED_PARAMETER(pDriverObject);
	NTSTATUS status = STATUS_SUCCESS;

	// Driver Exit
	TA_DEBUG_ONLY_PRINTLN("Driver ENTRY.");

	// Close the filter engine
	status = taFilterEngineClose(gDeviceObject);

	// Delete the device
	IoDeleteDevice(gDeviceObject);

	TA_DEBUG_ONLY_LOG_SUCCESS_STATUS("SUCCESS: Passed with no observable errors.", status);
}