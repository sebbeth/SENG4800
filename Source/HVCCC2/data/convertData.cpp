#include "convertData.h"

std::map<Stacker::Id, std::vector<StackerState>> convert(const std::map<Stacker::Id, std::vector<StackerEvent>>& source) {
	std::map<Stacker::Id, std::vector<StackerState>> result;
	//Iterate through every single event which is of the currently examined type (eg. stockpiles):
	for (auto eachSourceEntry : source) {
		auto eachDestinationEntry = result.emplace(std::piecewise_construct, std::make_tuple(eachSourceEntry.first), std::make_tuple()).first;
		auto eachState = StateTraits<StackerState>::initializeFromEvent(eachSourceEntry.second.front());
		(*eachDestinationEntry).second.reserve(eachSourceEntry.second.size());
		(*eachDestinationEntry).second.push_back(eachState);
		for (auto eachIt = ++(eachSourceEntry.second.begin()); eachIt != eachSourceEntry.second.end(); ++eachIt) {
			eachState = StateTraits<StackerState>::generateNextState(eachState, *eachIt);
			(*eachDestinationEntry).second.push_back(eachState);
		}
	}
	return result;
}
