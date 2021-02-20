#include "filters.h"



UINT64 gFilterInboundIdentifier;
UINT64 gFilterOutboundIdentifier;



/*
 * Creates the inbound filter with the provided engine handle.
 */
NTSTATUS taCreateFilterInbound(_In_ HANDLE engineHandle) {
	// Create an array to hold filter conditions
	FWPM_FILTER_CONDITION filterConditions[2] = {
		// Restrict protocol to only TCP
		{
			.fieldKey = FWPM_CONDITION_IP_PROTOCOL,
			.matchType = FWP_MATCH_EQUAL,
			.conditionValue = {
				.type = FWP_UINT8,
				.uint8 = IPPROTO_TCP,
			},
		},
		// Restrict remote port to the default 25565
		{
			.fieldKey = FWPM_CONDITION_IP_REMOTE_PORT,
			.matchType = FWP_MATCH_EQUAL,
			.conditionValue = {
				.type = FWP_UINT16,
				.uint16 = 25565,
			},
		},
	};

	// Create a struct to describe how the WFP filter will be created
	FWPM_FILTER filter = {
		.filterKey = TA_FILTER_INBOUND_GUID,
		.displayData = {
			.name = TA_FILTER_INBOUND_NAME,
			.description = TA_FILTER_INBOUND_DESCRIPTION,
		},
		.flags = 0,
		.layerKey = FWPM_LAYER_INBOUND_TRANSPORT_V4,
		.subLayerKey = TA_SUBLAYER_GUID,
		.weight = {
			.type = FWP_UINT8,
			.uint8 = 0xF,
		},
		.filterCondition = filterConditions,
		.numFilterConditions = 2,
		.action = {
			.type = FWP_ACTION_CALLOUT_TERMINATING,
			.calloutKey = TA_CALLOUT_INBOUND_GUID,
		},
	};

	// Attempt to add the inbound filter to the filter engine
	NTSTATUS status = FwpmFilterAdd(engineHandle, &filter, NULL, &gFilterInboundIdentifier);
	TA_DEBUG_ONLY_LOG_ERROR_STATUS("failed to add inbound filter", status);
	return status;
}



/*
 * Deletes the outbound filter with the provided engine handle.
 */
NTSTATUS taDeleteFilterInbound(_In_ HANDLE engineHandle) {
	// Attempt to delete the inbound filter from the filter engine
	NTSTATUS status = FwpmFilterDeleteById(engineHandle, gFilterInboundIdentifier);
	TA_DEBUG_ONLY_LOG_ERROR_STATUS("failed to delete inbound filter", status);
	return status;
}



/*
 * Creates the outbound filter with the provided engine handle.
 */
NTSTATUS taCreateFilterOutbound(_In_ HANDLE engineHandle) {
	// Create an array to hold filter conditions
	FWPM_FILTER_CONDITION filterConditions[2] = {
		// Restrict protocol to only TCP
		{
			.fieldKey = FWPM_CONDITION_IP_PROTOCOL,
			.matchType = FWP_MATCH_EQUAL,
			.conditionValue = {
				.type = FWP_UINT8,
				.uint8 = IPPROTO_TCP,
			},
		},
		// Restrict remote port to the default 25565
		{
			.fieldKey = FWPM_CONDITION_IP_REMOTE_PORT,
			.matchType = FWP_MATCH_EQUAL,
			.conditionValue = {
				.type = FWP_UINT16,
				.uint16 = 25565,
			},
		},
	};

	// Create a struct to describe how the WFP filter will be created
	FWPM_FILTER filter = {
		.filterKey = TA_FILTER_OUTBOUND_GUID,
		.displayData = {
			.name = TA_FILTER_OUTBOUND_NAME,
			.description = TA_FILTER_OUTBOUND_DESCRIPTION,
		},
		.flags = 0,
		.layerKey = FWPM_LAYER_OUTBOUND_TRANSPORT_V4,
		.subLayerKey = TA_SUBLAYER_GUID,
		.weight = {
			.type = FWP_UINT8,
			.uint8 = 0xF,
		},
		.filterCondition = filterConditions,
		.numFilterConditions = 2,
		.action = {
			.type = FWP_ACTION_CALLOUT_TERMINATING,
			.calloutKey = TA_CALLOUT_OUTBOUND_GUID,
		},
	};

	// Attempt to add the outbound filter to the filter engine
	NTSTATUS status = FwpmFilterAdd(engineHandle, &filter, NULL, &gFilterOutboundIdentifier);
	TA_DEBUG_ONLY_LOG_ERROR_STATUS("failed to add outbound filter", status);
	return status;
}



/*
 * Deletes the outbound filter with the provided engine handle.
 */
NTSTATUS taDeleteFilterOutbound(_In_ HANDLE engineHandle) {
	// Attempt to delete the outbound filter from the filter engine
	NTSTATUS status = FwpmFilterDeleteById(engineHandle, gFilterOutboundIdentifier);
	TA_DEBUG_ONLY_LOG_ERROR_STATUS("failed to delete outbound filter", status);
	return status;
}