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