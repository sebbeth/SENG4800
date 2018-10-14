#pragma once
#include <vector>
#include "GameFramework/Actor.h"
//specialise this for each entity, specifying the associated actor type
template<typename Entity>
struct u_actor_type {
	using type = AActor;
};

template<typename Entity>
using UActorType = typename u_actor_type<Entity>::type;

template<typename _Entity>
class SimulationData
{
public:
	using Entity = _Entity;
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

	SimulationData(const std::vector<typename Entity::AssociatedState>& states, Actor* actorPointer, bool isBeingRendered);
};

template<typename Entity>
using DataMap = std::map<
	typename Entity::Id,
	SimulationData<Entity>
>;

template<typename... Entities>
using DataMapTuple = std::tuple<DataMap<Entities>...>;

template<typename _Entity>
SimulationData<_Entity>::SimulationData(const std::vector<typename Entity::AssociatedState>& states, Actor* actorPointer, bool isBeingRendered) : states(states), stateWindow(this->states.begin(), this->states.begin()), actorPointer(actorPointer), isBeingRendered(isBeingRendered) {
}

