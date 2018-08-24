#pragma once

#include "python/out/extractData.h"

#include <vector>
#include <string>
#include <map>

#include "python/out/DumpStation/DumpStationState.h"
#include "python/out/DumpStation/DumpStationStateTraits.h"
#include "python/out/LoadPoint/LoadPointState.h"
#include "python/out/LoadPoint/LoadPointStateTraits.h"
#include "python/out/Reclaimer/ReclaimerState.h"
#include "python/out/Reclaimer/ReclaimerStateTraits.h"
#include "python/out/ShipLoader/ShipLoaderState.h"
#include "python/out/ShipLoader/ShipLoaderStateTraits.h"
#include "python/out/Signal/SignalState.h"
#include "python/out/Signal/SignalStateTraits.h"
#include "python/out/Stacker/StackerState.h"
#include "python/out/Stacker/StackerStateTraits.h"
#include "python/out/Stockpile/StockpileState.h"
#include "python/out/Stockpile/StockpileStateTraits.h"
#include "python/out/Train/TrainState.h"
#include "python/out/Train/TrainStateTraits.h"
#include "python/out/Vessel/VesselState.h"
#include "python/out/Vessel/VesselStateTraits.h"


//notice that the state maps exist only for stacker not reclaimer; stacker and reclaimer events are (for now) merged into stacker events, with  amount negated for reclaimation; it may never actually get used or we may have to improve use of amount later
typedef std::tuple<
	std::map<std::string, std::vector<DumpStationState>>,
	std::map<std::string, std::vector<LoadPointState>>,
	std::map<std::string, std::vector<ShipLoaderState>>,
	std::map<std::string, std::vector<SignalState>>,
	std::map<std::string, std::vector<StackerState>>,
	std::map<std::string, std::vector<StockpileState>>,
	std::map<std::string, std::vector<TrainState>>,
	std::map<int, std::vector<VesselState>>
> StateMapTuple;

template<typename Event, typename IdType>
void convertEvents(const EventVectorTuple& source, StateMapTuple& destination, const IdType Event::* idPtr);

StateMapTuple convertAll(const EventVectorTuple& source);

//note that this is a bit of a hack in terms of getting ids, and eventually eachEvent event/state class should define it's own key identifier type + a getter for it (defined by hand); but this works for now
template<typename Event, typename IdType>
void convertEvents(const EventVectorTuple& source, StateMapTuple& destination, const IdType Event::* idPtr) {
	const std::vector<Event>& sourceTarget = std::get<std::vector<Event>>(source); 
	std::map<IdType, std::vector<Event::AssociatedState>>& destinationTarget = std::get<std::map<IdType, std::vector<typename Event::AssociatedState>>>(destination);
	for (const Event& eachEvent : sourceTarget) {
		const IdType& eachId = eachEvent.*idPtr;
		auto it = destinationTarget.find(eachId);
		if (it == destinationTarget.end()) {
			auto entry = destinationTarget.emplace(std::piecewise_construct, std::make_tuple(eachId), std::make_tuple()).first;
			(*entry).second.emplace_back(StateTraits<Event::AssociatedState>::initializeFromEvent(eachEvent));
		}
		else {
			(*it).second.push_back(StateTraits<Event::AssociatedState>::generateNextState((*it).second.back(), eachEvent));
		}
	}
}