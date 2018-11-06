/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#pragma once
#include "../util.h"
#include <map>
#include <tuple>

#include "Stockpile/Stockpile.h"
#include "Stockpile/StockpileEvent.h"
#include "Stockpile/StockpileState.h"
#include "Stacker/Stacker.h"
#include "Stacker/StackerEvent.h"
#include "Stacker/StackerState.h"
#include "Reclaimer/Reclaimer.h"
#include "Reclaimer/ReclaimerEvent.h"
#include "Reclaimer/ReclaimerState.h"
#include "Dumpstation/Dumpstation.h"
#include "Dumpstation/DumpstationEvent.h"
#include "Dumpstation/DumpstationState.h"
#include "Loadpoints/Loadpoints.h"
#include "Loadpoints/LoadpointsEvent.h"
#include "Loadpoints/LoadpointsState.h"
#include "Vessel/Vessel.h"
#include "Vessel/VesselEvent.h"
#include "Vessel/VesselState.h"
#include "Shiploader/Shiploader.h"
#include "Shiploader/ShiploaderEvent.h"
#include "Shiploader/ShiploaderState.h"
#include "TrainMovement/TrainMovement.h"
#include "TrainMovement/TrainMovementEvent.h"
#include "TrainMovement/TrainMovementState.h"
#include "StackerReclaimer/StackerReclaimer.h"
#include "StackerReclaimer/StackerReclaimerState.h"

#define EntitiesWithEvents Dumpstation, Loadpoints, Reclaimer, Shiploader, Stacker, Stockpile, TrainMovement, Vessel
#define MergeEntities StackerReclaimer
#define AllEntities Dumpstation, Loadpoints, Reclaimer, Shiploader, Stacker, StackerReclaimer, Stockpile, TrainMovement, Vessel