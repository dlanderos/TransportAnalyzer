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



#include "tcp_utils.h"



/*
 * Determines if the provided flag is set by checking the TCP header data.
 * The header data is expected to begin at the pointer's address. Offsets are
 * not handled.
 */
BOOL taTCPFlagSet(_In_ PBYTE header, BYTE flag) {
	BYTE flags = *(header + 13);
	if (flags & flag) {
		return TRUE;
	}
	return FALSE;
}



/*
 * Will return the provided string if the flag is present, otherwise returns an empty string.
 */
PCHAR _flagStringOrEmpty(_In_ PBYTE header, BYTE flag, PCHAR string) {
	if (taTCPFlagSet(header, flag)) {
		return string;
	}
	return "";
}



/*
 * Prints all the TCP flags (except for NS) that are set in the TCP header.
 */
VOID taTCPPrintFlags(_In_ PBYTE header) {
	DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "Flags: %s%s%s%s%s%s%s%s\n",
		_flagStringOrEmpty(header, TCP_FLAG_CWR, "CWR "),
		_flagStringOrEmpty(header, TCP_FLAG_ECE, "ECE "),
		_flagStringOrEmpty(header, TCP_FLAG_URG, "URG "),
		_flagStringOrEmpty(header, TCP_FLAG_ACK, "ACK "),
		_flagStringOrEmpty(header, TCP_FLAG_PSH, "PSH "),
		_flagStringOrEmpty(header, TCP_FLAG_RST, "RST "),
		_flagStringOrEmpty(header, TCP_FLAG_SYN, "SYN "),
		_flagStringOrEmpty(header, TCP_FLAG_FIN, "FIN")
	);
}



/*
 * Get's the checksum of the TCP packet.
 */
UINT16 taTCPGetChecksum(_In_ PBYTE header) {
	BYTE upper = *(header + 16);
	BYTE lower = *(header + 17);
	UINT16 value = (((UINT16) upper) << 8) | lower;
	return value;
}



/*
 * Put's a little-endian byte written in ones and zeroes into the provided string.
 * That string must be 9 characters long. 8 for the ones and zeroes, and 1 for the
 * string terminator.
 */
VOID taTCPPrettyByte(_In_ BYTE value, _Inout_ PCHAR string) {
	for (UINT32 index = 0; index < 8; index++) {
		if ((0x80 >> index) & value) {
			string[index] = '1';
		}
		else {
			string[index] = '0';
		}
	}
	string[8] = '\0';
}