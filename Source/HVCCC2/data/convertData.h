#pragma once
#include <vector>
#include <map>

#include "extraction/implementedEntities.h"
#include "extraction/implementedTraits.h"
#include "extraction/extractData.h"

template<typename Entity>
using EventMap = std::map<typename Entity::Id, std::vector<typename Entity::AssociatedEvent>>;

template<typename... Entities>
using EventMapTuple = std::tuple<EventMap<Entities>...>;

template<typename Entity>
using StateMap = std::map<typename Entity::Id, std::vector<typename Entity::AssociatedState>>;

template<typename... Entities>
using StateMapTuple = std::tuple<StateMap<Entities>...>;

namespace convert_data_detail {
	template<typename... Entities>
	struct convert_functor {
		using Destination = StateMapTuple<Entities...>;
		Destination& destination;
		template<typename Each>
		inline void operator() (const Each& each) {
			using Event = typename Each::mapped_type::value_type;
			std::get<StateMap<typename Event::Entity>>(destination) = convert(each);
		}
		convert_functor(Destination& destination) : destination(destination) {}
	};
}

template<typename... Entities>
using ConvertFunctor = convert_data_detail::convert_functor<Entities...>;

template<typename Each, typename Event = typename Each::mapped_type::value_type>
StateMap<typename Event::Entity> convert(const Each& source) {
	StateMap<typename Event::Entity> result;
	//Iterate through every single event which is of the currently examined type (eg. stockpiles):
	for (auto& eachSourceEntry : source) {
		auto eachDestinationEntry = result.emplace(std::piecewise_construct, std::make_tuple(eachSourceEntry.first), std::make_tuple()).first;
		auto eachState = StateTraits<typename Event::Entity::AssociatedState>::initializeFromEvent(eachSourceEntry.second.front());
		(*eachDestinationEntry).second.reserve(eachSourceEntry.second.size());
		(*eachDestinationEntry).second.push_back(eachState);
		for (auto eachIt = ++(eachSourceEntry.second.begin()); eachIt != eachSourceEntry.second.end(); ++eachIt) {
			eachState = StateTraits<typename Event::Entity::AssociatedState>::generateNextState(eachState, *eachIt);
			(*eachDestinationEntry).second.push_back(eachState);
		}
	}
	return result;
}

template<typename Mergable, typename... Entities>
void merge(StateMapTuple<Entities...>& source, StateMap<Mergable>& destination);

template<typename Source>
void merge(Source& source, StateMap<StackerReclaimer>& destination) {

	auto& stackerMap = std::get<StateMap<Stacker>>(source);
	auto& reclaimerMap = std::get<StateMap<Reclaimer>>(source);
	auto stackerEntryIt = stackerMap.begin();
	auto reclaimerEntryIt = reclaimerMap.begin();

	//put all the matching states in the destination in-order
	while (stackerEntryIt != stackerMap.end() || reclaimerEntryIt != reclaimerMap.end()) {
		//move through stacker entries until we are at least up to the reclaimer entry
		while (stackerEntryIt != stackerMap.end() && (reclaimerEntryIt == reclaimerMap.end() || (*stackerEntryIt).first < (*reclaimerEntryIt).first)) {
			++stackerEntryIt;
		}

		//move through reclaimer eentries until we are at least up to the stacker entry
		while (reclaimerEntryIt != reclaimerMap.end() && (stackerEntryIt == stackerMap.end() || (*reclaimerEntryIt).first < (*stackerEntryIt).first)) {
			++reclaimerEntryIt;
		}

		//if matching, extract the states from the merge sources and put them into the merge destination, in-order
		if ((*reclaimerEntryIt).first == (*stackerEntryIt).first) {

			auto eachDestinationEntry = destination.emplace(std::piecewise_construct, std::make_tuple((*reclaimerEntryIt).first), std::make_tuple()).first;
			auto stackerStateIt = (*stackerEntryIt).second.begin();
			auto reclaimerStateIt = (*reclaimerEntryIt).second.begin();

			//put all the matching states in the destination in-order
			while (stackerStateIt != (*stackerEntryIt).second.end() || reclaimerStateIt != (*reclaimerEntryIt).second.end()) {
				//move through and add stacker states until we are at least up to the reclaimer state, breaking any ties (which shouldn't occur) but just picking the reclaimer state
				while (stackerStateIt != (*stackerEntryIt).second.end() && (reclaimerStateIt == (*reclaimerEntryIt).second.end() || (*stackerStateIt).time <= (*reclaimerStateIt).time)) {
					(*eachDestinationEntry).second.push_back(*stackerStateIt);
					++stackerStateIt;
				}

				//move through and add reclaimer states until we are at least up to the stacker state
				while (reclaimerStateIt != (*reclaimerEntryIt).second.end() && (stackerStateIt == (*stackerEntryIt).second.end() || (*reclaimerStateIt).time < (*stackerStateIt).time)) {
					(*eachDestinationEntry).second.emplace_back(*reclaimerStateIt);
					++reclaimerStateIt;
				}
			}

			//remove the entries from the source and update the stored entries to the next available
			stackerEntryIt = stackerMap.erase(stackerEntryIt);
			reclaimerEntryIt = reclaimerMap.erase(reclaimerEntryIt);
		}
	}
}