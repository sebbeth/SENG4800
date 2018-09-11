/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 15:53:43.172985
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
#include "Signal/Signal.h"
#include "Signal/SignalEvent.h"
#include "Signal/SignalState.h"
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
#include "StackerReclaimer/StackerReclaimer.h"
#include "StackerReclaimer/StackerReclaimerState.h"

#define EntitiesWithEvents Dumpstation, Loadpoints, Reclaimer, Shiploader, Signal, Stacker, Stockpile, Vessel
#define MergeEntities StackerReclaimer
#define AllEntities Dumpstation, Loadpoints, Reclaimer, Shiploader, Signal, Stacker, StackerReclaimer, Stockpile, Vessel

using EventMapTuple = std::tuple<std::map<Dumpstation::Id, std::vector<DumpstationEvent>>, std::map<Loadpoints::Id, std::vector<LoadpointsEvent>>, std::map<Reclaimer::Id, std::vector<ReclaimerEvent>>, std::map<Shiploader::Id, std::vector<ShiploaderEvent>>, std::map<Signal::Id, std::vector<SignalEvent>>, std::map<Stacker::Id, std::vector<StackerEvent>>, std::map<Stockpile::Id, std::vector<StockpileEvent>>, std::map<Vessel::Id, std::vector<VesselEvent>>>;
using BasicStateMapTuple = std::tuple<std::map<Dumpstation::Id, std::vector<DumpstationState>>, std::map<Loadpoints::Id, std::vector<LoadpointsState>>, std::map<Reclaimer::Id, std::vector<ReclaimerState>>, std::map<Shiploader::Id, std::vector<ShiploaderState>>, std::map<Signal::Id, std::vector<SignalState>>, std::map<Stacker::Id, std::vector<StackerState>>, std::map<Stockpile::Id, std::vector<StockpileState>>, std::map<Vessel::Id, std::vector<VesselState>>>;
using FullStateMapTuple = std::tuple<std::map<Dumpstation::Id, std::vector<DumpstationState>>, std::map<Loadpoints::Id, std::vector<LoadpointsState>>, std::map<Reclaimer::Id, std::vector<ReclaimerState>>, std::map<Shiploader::Id, std::vector<ShiploaderState>>, std::map<Signal::Id, std::vector<SignalState>>, std::map<Stacker::Id, std::vector<StackerState>>, std::map<StackerReclaimer::Id, std::vector<StackerReclaimerState>>, std::map<Stockpile::Id, std::vector<StockpileState>>, std::map<Vessel::Id, std::vector<VesselState>>>;
