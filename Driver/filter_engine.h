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



#ifndef TA_FILTER_ENGINE_H
#define TA_FILTER_ENGINE_H



#include "common.h"
#include "debug.h"
#include "sublayers.h"
#include "callouts.h"
#include "filters.h"



/*
 * Begin the setup process for the filter engine. In the event the filter engine isn't running,
 * it will setup a hook to listen for when it starts and it can then commit a transaction. If it's
 * already running, the transaction can be begun immediately.
 */
NTSTATUS taFilterEngineBegin(_In_ PDEVICE_OBJECT pDeviceObject);



/*
 * Begin and commit the filter engine transaction. Adds the filters, sublayers, and callouts. 
 */
NTSTATUS taFilterEngineOpen(_In_ PDEVICE_OBJECT pDeviceObject);



/*
 * Closes the filter engine and frees resources that are no longer needed.
 */
NTSTATUS taFilterEngineClose(_In_ PDEVICE_OBJECT pDeviceObject);



#endif // !TA_FILTER_ENGINE_H