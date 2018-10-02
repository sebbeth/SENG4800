#include "StockpileData.h"
SimulationData<Stockpile>::SimulationData(const std::vector<typename Entity::AssociatedState>& states, Actor* actorPointer, bool isBeingRendered) : states(states), stateWindow(this->states.begin(), this->states.begin()), actorPointer(actorPointer), isBeingRendered(isBeingRendered), maximumAmount(0) {
	for (auto& each : states) {
		if (each.amount > maximumAmount) {
			maximumAmount = each.amount;
		}
	}
}