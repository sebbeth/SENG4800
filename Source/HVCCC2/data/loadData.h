#pragma once
#include "extraction/extractData.h"
#include <map>
#include <vector>

#include "convertData.h"
#include "serialization.h"
namespace load_data_detail {
	template<typename... Entities>
	struct map_and_sort_functor {
		using Destination = EventMapTuple<Entities...>;
		Destination& destination;

		//template<typename T>
		//struct is_same_partial_impl {
		//	template<typename U>
		//	struct detail {
		//		static const bool value = std::is_same<T, U>::value;
		//	};
		//};
		//template<typename T>
		//using is_same_partial = typename is_same_partial_impl<T>::detail;
		//using tmp = ConditionalAny<typename is_same_partial_impl<Stacker>::detail, Entities...>;

		template<typename Event>
		inline void operator() (const std::vector<Event>& each) {
			std::get<EventMap<typename Event::Entity>>(destination) = mapAndSort(each);
		}

		map_and_sort_functor(Destination& destination): destination(destination) {}
	};
}

template<typename... Entities>
using MapAndSortFunctor = load_data_detail::map_and_sort_functor<Entities...>;

/**
 * pair<data, success/fail>
 */
std::pair<EventVectorTuple, bool> getEventsFromXMLFolder(const std::string& xmlFolderPath);

/**
 * pair<data, success/fail>
 */
std::pair<StateMapTuple<AllEntities>, bool> loadXMLData(const std::string& srcPath);

/**
 * pair<data, success/fail>
 */
std::pair<StateMapTuple<AllEntities>, bool> loadBinaryData(const std::string& srcPath);

template<typename Event>
EventMap<typename Event::Entity> mapAndSort(const std::vector<Event>& source) {
	EventMap<typename Event::Entity> result;
	for (auto& eachEvent : source) {
		auto eachId = eachEvent.id;
		//This variable is used to find out whether the std::pair for the
		//currently examined object (eg. stockpile with stockpileID "CCT1392.1")
		//has been created or not:
		auto entryIterator = result.find(eachId);

		if (entryIterator == result.end()) {
			//If the std::pair for the currently examined object has not been created,
			//create entryIterator and place the initial creation state at the front of the vector
			//of states:
			entryIterator = result.emplace(std::piecewise_construct, std::make_tuple(eachId), std::make_tuple()).first;
		}
		(*entryIterator).second.push_back(eachEvent);
	}

	//now do the sort
	for (auto& eachEntry : result) {
		std::sort(eachEntry.second.begin(), eachEntry.second.end(), [](const Event& a, const Event& b) {return a.time < b.time; });
	}
	return result;
}
