#pragma once
#include <vector>
#include "SimulationData.h"
#include "../extraction/Stockpile/Stockpile.h"
#include "../../CoalStack.h"

template<>
struct u_actor_type<Stockpile> {
	using type = ACoalStack;
};


template<>
class SimulationData<Stockpile>
{
public:
	using Entity = Stockpile;
	using Actor = typename UActorType<Entity>;
	using State = typename Entity::AssociatedState;
	std::vector<State> states;
	using const_iterator = typename std::vector<State>::const_iterator;

	//a sliding window into the state list which direct to the states surrounding the current moment in simulation time
	std::pair<const_iterator, const_iterator> stateWindow; //note that if the list of states is modified these iterators will be invalidated and must be replaced
	
	//Unreal Engine Actor pointer
	Actor* actorPointer;

	//whether or not this actor is within render distance/needs to be updated
	bool isBeingRendered;

	//the maximum amount in any of the states
	double maximumAmount;

	SimulationData(const std::vector<typename Entity::AssociatedState>& states, Actor* actorPointer, bool isBeingRendered);
};