#include "VesselData.h"
SimulationData<Vessel>::SimulationData(const std::vector<typename Entity::AssociatedState>& states, Actor* actorPointer, bool isBeingRendered) : states(states), stateWindow(this->states.begin(), this->states.begin()), actorPointer(actorPointer), isBeingRendered(isBeingRendered), terminal(TerminalId::Invalid), berthPosition(NAN) {
}

void SimulationData<Vessel>::determineArrivalLocation(const DataMapTuple<AllEntities>& data) {
	for (auto& eachEntity : std::get<DataMap<Shiploader>>(data)) {
		for (auto& eachState : eachEntity.second.states) {
			if (eachState.vesselID == states[0].id) {
				terminal = eachState.id.terminal;
				berthPosition = eachState.position;
				break;
			}

		}
	}
}
