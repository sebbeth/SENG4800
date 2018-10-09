// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "data/serialization.h"
#include "data/extraction/implementedEntities.h"
#include "data/simulation/SimulationData.h"
#include "data/simulation/StockpileData.h"
#include "data/extraction/TerminalId.h"
#include "data/extraction/TrainMovement/TrainMovement.h"
#include "StackerReclaimer.h"
#include "CoalStack.h"
#include "Ship.h"
#include "ShipLoader.h"
//#include "TrainMovement.h"
#include "TrainTrackSpline.h"
#include "Train.h"


#include "LevelController.generated.h"

template<typename Entity>
using DataMap = std::map<
	typename Entity::Id,
	SimulationData<Entity>
>;

template<typename... Entities>
using DataMapTuple = std::tuple<DataMap<Entities>...>;

class ALevelController;

//TODO: These functors might actually benifit from using a common base class and virtualised overloading of the each-operator (if that exists?)
struct AddToSimFunctor {
	ALevelController* context;
	template<typename Each>

	//add each entity from the statemaptuple into the datamaptuple
	void operator()(const Each& eachStateMap);

	AddToSimFunctor(); //set context to a nullptr because unreal wants a default constructor
	AddToSimFunctor(ALevelController* context);
};

struct UpdateWindowsFunctor {
	ALevelController* context;
	/**
	 * Updates the sliding state-windows for a given Entity type so they point towards the state(s) corresponding to the current simulation time
	 * Note: only bothers with entities that are going to be rendered
	 * Note: Each is a DataMap<Entity> for some Entity
	 */
	template<typename Each>
	void operator()(Each& eachDataMap);

	UpdateWindowsFunctor(); //set context to a nullptr because unreal wants a default constructor
	UpdateWindowsFunctor(ALevelController* context);
};

struct AnimateEntitiesFunctor {
	ALevelController* context;
	/**
	 * Animates all the actors for a given entity type (by calling ALevelController.animateActor() for each)
	 * Note: only bothers with entities that are going to be rendered
	 * Note: Each is a DataMap<Entity> for some Entity
	 */
	template<typename Each>
	void operator()(Each& eachDataMap);

	AnimateEntitiesFunctor(); //set context to a nullptr because unreal wants a default constructor
	AnimateEntitiesFunctor(ALevelController* context);
};

//gets the minimum and maximum timepoints in the simulation and stores it into the context
struct FindSimTimeBoundsFunctor {
	ALevelController* context;
	/**
	 * Updates the simStartTime and simEndTime to be at least as low and high (respectively) as the lowest and highest time seen in the data
	 */
	template<typename Each>
	void operator()(const Each& eachDataMap);

	/**
	 * Updates the simStartTime and simEndTime to be at least as low and high (respectively) as the lowest and highest time seen in the data
	 * note: this overload calls the forEachInTuple
	 */
	void operator()();

	FindSimTimeBoundsFunctor(); //set context to a nullptr because unreal wants a default constructor
	FindSimTimeBoundsFunctor(ALevelController* context);
};

//gets the minimum and maximum timepoints in the simulation and stores it into the context
struct ClearDataFunctor {
	ALevelController* context;
	/**
	 * Clears the existing entities for the data in the msp
	 */
	template<typename Each>
	void operator()(Each& eachDataMap);
	/**
	 * Updates the simStartTime and simEndTime to be at least as low and high (respectively) as the lowest and highest time seen in the data
	 * note: this overload calls the forEachInTuple
	 */
	void operator()();

	ClearDataFunctor(); //set context to a nullptr because unreal wants a default constructor
	ClearDataFunctor(ALevelController* context);
};

//Note/TODO: cheating by using the states instead of events for now
struct StringifyEventsFunctor {
	ALevelController* context;
	std::vector<std::pair<float, std::string>> interimResult;

	/**
	 * Gets a string describing each of the events/states in the map
	 */
	template<typename Each>
	void operator()(Each& eachDataMap);

	/**
	 * Gets a string describing each of the events/states in the context's current data
	 */
	TArray<FString> operator()();

	StringifyEventsFunctor(); //set context to a nullptr because unreal wants a default constructor
	StringifyEventsFunctor(ALevelController* context);
};

//tis struct this needed for all data types being spawned and animated, as well as a getorspawnactor and anamiteenity method
template<>
struct u_actor_type<StackerReclaimer> {
	using type = AStackerReclaimer;
};

template<>
struct u_actor_type<Shiploader> {
	using type = AShipLoader;
};

template<>
struct u_actor_type<Vessel> {
	using type = AShip;
};

/*
template<>
struct u_actor_type<TrainMovement> {
	using type = ATrain;
};*/

template<>
struct u_actor_type<TrainMovement> {
	using type = ATrain;
};


UCLASS()
class HVCCC2_API ALevelController : public AActor
{
	GENERATED_BODY()

	friend struct AddToSimFunctor;
	friend struct UpdateWindowsFunctor;
	friend struct AnimateEntitiesFunctor;
	friend struct FindSimTimeBoundsFunctor;
	friend struct ClearDataFunctor;
	friend struct StringifyEventsFunctor;

	AddToSimFunctor addToSimFunctor;
	UpdateWindowsFunctor updateWindowsFunctor;
	AnimateEntitiesFunctor animateEntitiesFunctor;
	FindSimTimeBoundsFunctor findSimTimeBoundsFunctor;
	ClearDataFunctor clearDataFunctor;
	StringifyEventsFunctor stringifyEventsFunctor;
	/*double xMin, xMax;*/

	double simTime;
	double simStartTime, simEndTime;

	double speed;
	bool isPlaying;

	DataMapTuple<AllEntities> data;

	//garbage collection point for the unreal engine actors; stored here instead of instead the main data tuple as it's the easiest way to ensure garbage collection is done safely
	TArray<AActor*> actorPointers;
	
public:	
	// Sets default values for this actor's properties
	ALevelController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Get the blueprints to be used
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AStackerReclaimer> largeSR_blueprint;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AStackerReclaimer> stacker_blueprint;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AStackerReclaimer> reclaimer_blueprint;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AShipLoader> ship_loader_blueprint;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AShip> ship_blueprint;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ATrain> train_locomotive_blueprint;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACoalStack> coal_stack_blueprint;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AConveyorBelt> conveyor_belt_blueprint;

	

	//Train and track actors
	UPROPERTY(EditAnywhere)
		TArray<ATrain*> trains;
	//UPROPERTY(EditAnywhere)
	//	TArray<ATrackSpline*> trainTracks;
	UPROPERTY(EditAnywhere)
		TArray<ATrainTrackSpline*> trainTracks;




	// NCT Actor Arrays
	UPROPERTY(EditAnywhere)
	TArray<ACoalStack*> coalStacks;
	UPROPERTY(EditAnywhere)
	TArray<AStackerReclaimer*> stackerReclaimers;
	UPROPERTY(EditAnywhere)
	TArray<AShipLoader*> shipLoaders;
	UPROPERTY(EditAnywhere)
	TArray<AShip*> ships;
	UPROPERTY(EditAnywhere)
	TArray<AConveyorBelt*> conveyorBelts; 
	// Koorigang Stacker Reclaimer track markers
	UPROPERTY(EditAnywhere)
		TArray<AActor*> NCT_SR_rails_start;
	UPROPERTY(EditAnywhere)
		TArray<AActor*> NCT_SR_rails_end;
	// Koorigang ship loader track markers
	UPROPERTY(EditAnywhere)
		TArray<AActor*> NCT_loader_rails_start;
	UPROPERTY(EditAnywhere)
		TArray<AActor*> NCT_loader_rails_end;
	// Ship berth position markers
	UPROPERTY(EditAnywhere)
		TArray<AActor*> NCT_berths;
	//Coal Pad position markers
	UPROPERTY(EditAnywhere)
		TArray<AActor*> NCT_pads_start;
	UPROPERTY(EditAnywhere)
		TArray<AActor*> NCT_pads_end;



	//KCT Actor Arrays
	UPROPERTY(EditAnywhere)
		TArray<AConveyorBelt*> conveyorBeltsKCT;
	/*
	UPROPERTY(EditAnywhere)
		TArray<ACoalStack*> coalStacksKCT;
	UPROPERTY(EditAnywhere)
		TArray<AStackerReclaimer*> stackerReclaimersKCT;
	UPROPERTY(EditAnywhere)
		TArray<AShipLoader*> shipLoadersKCT;
	UPROPERTY(EditAnywhere)
		TArray<AShip*> shipsKCT;
		*/
	UPROPERTY(EditAnywhere)
		TArray<AActor*> KCT_SR_rails_start;
	UPROPERTY(EditAnywhere)
		TArray<AActor*> KCT_SR_rails_end;
	// Koorigang ship loader track markers
	UPROPERTY(EditAnywhere)
		TArray<AActor*> KCT_loader_rails_start;
	UPROPERTY(EditAnywhere)
		TArray<AActor*> KCT_loader_rails_end;
	// Ship berth position markers
	UPROPERTY(EditAnywhere)
		TArray<AActor*> KCT_berths;
	//Coal Pad position markers
	UPROPERTY(EditAnywhere)
		TArray<AActor*> KCT_pads_start;
	UPROPERTY(EditAnywhere)
		TArray<AActor*> KCT_pads_end;


	//CCT Actor Arrays

	//Conveyor Belt position markers
	/*
	UPROPERTY(EditAnywhere)
		TArray<AConveyorBelt*> conveyorBeltsCCT;
	UPROPERTY(EditAnywhere)
		TArray<ACoalStack*> coalStacksCCT;
	UPROPERTY(EditAnywhere)
		TArray<AStackerReclaimer*> stackerReclaimersCCT;
	UPROPERTY(EditAnywhere)
		TArray<AShipLoader*> shipLoadersCCT;
	UPROPERTY(EditAnywhere)
		TArray<AShip*> shipsCCT;

	*/

	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//loading/applying data
	/**
	 * the return type indicates whether or not it succeeds
	 */
	UFUNCTION(BlueprintCallable, Category = "data")
	bool loadXMLData(const FString& srcPath);

	UFUNCTION(BlueprintCallable, Category = "data")
	TArray<FString> getEventMessages();

	//time controls
	UFUNCTION(BlueprintCallable, Category = "time")
	float getSimTime();
	UFUNCTION(BlueprintCallable, Category = "time")
	float getSimStart();
	UFUNCTION(BlueprintCallable, Category = "time")
	float getSimEndTime();
	UFUNCTION(BlueprintCallable, Category = "time")
	void setSimTime(float absoluteTime);
	UFUNCTION(BlueprintCallable, Category = "time")
	void moveSimTime(float deltaTime);
	UFUNCTION(BlueprintCallable, Category = "time")
	float getPlaySpeed();
	UFUNCTION(BlueprintCallable, Category = "time")
	void setPlaySpeed(float speed);

	//true if playing, false if paused
	UFUNCTION(BlueprintCallable, Category = "time")
	bool getPlayState();

	//true if playing, false if paused
	UFUNCTION(BlueprintCallable, Category = "time")
	void setPlayState(bool isPlaying);

private:
	
	AStackerReclaimer * spawnAStackerReclaimer(FString id, int trackId, FVector railStart, FVector railEnd, TSubclassOf<class AStackerReclaimer> blueprint);
	AShipLoader * spawnAShipLoader(FString id, FVector railStart, FVector railEnd, TSubclassOf<class AShipLoader> blueprint);
	AShip * spawnAShip(FString id, FVector position, FRotator rotator, TSubclassOf<class AShip> blueprint);
	AConveyorBelt * spawnAConveyorBelt(FString id, FVector position, FRotator rotator, TSubclassOf<class AConveyorBelt> blueprint);
	ACoalStack * spawnACoalStack(FString id, FVector position, FRotator rotator, float width, TSubclassOf<class ACoalStack> blueprint);
	ATrain * spawnATrain(FString id, FVector position, TSubclassOf<class ATrain> blueprint);

	ATrain * spawnATrain(FString id, FVector position, FRotator rotator,TSubclassOf<class ATrain> blueprint);


	template<typename Id>
	UActorType<typename Id::Entity>* getOrSpawnActor(const typename Id& id);

	int getIndexOfStackerReclaimer(TArray<AStackerReclaimer*> array, AStackerReclaimer* actor);

	AStackerReclaimer* getOrSpawnActor(const StackerReclaimer::Id& id);
	AShip* getOrSpawnActor(const Vessel::Id& id);
	ACoalStack* getOrSpawnActor(const Stockpile::Id& id);
	AShipLoader* getOrSpawnActor(const Shiploader::Id& id);

	ATrain* getOrSpawnActor(const TrainMovement::Id& id);


	/**
	 * Exposes all the information about an entity for animation; defaults to calling a function exposing less information for backward compatibility;
	 * interpolationScale is how far towards nextState the current time is from previousState. The scale is from 0.0 to 1.0; at 0.0 the current time is exactly that of previousState; at 1.0 the current time is exactly that of nextState
	 * Note: it is not necessary to add inline when overloading this yourself
	 */
	template<typename Entity>
	inline void animateEntity(const SimulationData<Entity>& data, float interpolationScale);

	//void animateEntity(const SimulationData<TrainMovement>& data, float interpolationScale);
	/**
	 * Uses only the ends of the window and the interpolationScale to animate an entity
	 * interpolationScale is how far towards nextState the current time is from previousState. The scale is from 0.0 to 1.0; at 0.0 the current time is exactly that of previousState; at 1.0 the current time is exactly that of nextState
	 */
	template<typename Actor, typename State>
	void animateEntity(Actor* actorPointer, const typename State& previousState, const typename State& nextState, float interpolationScale);
	
	void animateEntity(AStackerReclaimer* actorPointer, const StackerReclaimerState& previousState, const StackerReclaimerState& nextState, float interpolationScale);
	void animateEntity(AShip* actorPointer, const VesselState& previousState, const VesselState& nextState, float interpolationScale);
	//void animateEntity(ACoalStack* actorPointer, const StockpileState& previousState, const StockpileState& nextState, float interpolationScale);
	void animateEntity(const SimulationData<Stockpile>& data, float interpolationScale);
	void animateEntity(AShipLoader* actorPointer, const ShiploaderState& previousState, const ShiploaderState& nextState, float interpolationScale);

	//void animateEntity(ATrain* actorPointer, const TrainMovementState& previousState, const TrainMovementState& nextState, float interpolationScale);
	void animateEntity(const SimulationData<TrainMovement>& data, float interpolationScale);

	void stackCoal(int stackerId);
	void stopStackingCoal(int stackerId);

	void reclaimCoal(int stackerId, int loaderId);
	void stopReclaimingCoal(int stackerId, int loaderId);


	// Helper functions, don't call these directy
	void setCoalStackingState(int stackerId, int state);
	void setCoalReclaimingState(int stackerId,int loaderId, int state);

	// Pad lengths
	int getPadLength(TerminalId terminalId, const std::string& padId);
	int getPadLength(TerminalId TerminalId, const int& padId);
	int getTrackLength(TerminalId TerminalId, const int& trackID);
	int getShipLoaderTrackLength(TerminalId terminal);

	// Pad location
	//void setStockPileLocation(ACoalStack* actorPointer, const Stockpile::Id& id, std::string padId, double position);

	int testTime; // Just being used for testing

};

template<typename Id>
UActorType<typename Id::Entity>* ALevelController::getOrSpawnActor(const typename Id& id) {
	/*default implementation for entities that aren't spawned/animated yet*/
	return nullptr;
}

template<typename Entity>
inline void ALevelController::animateEntity(const SimulationData<Entity>& data, float interpolationScale) {
	//Commented out code provides hinting on types, and an example of how to get the variables used in the simpler animateEntity
	using Actor = UActorType<Entity>;
	//using State = typename Entity::State;
	Actor* actorPointer = data.actorPointer;
	//const State& beforeState = (*data.stateWindow.first);
	//const State& afterState = (*data.stateWindow.second);

	//note that the pointer stored in data is a const pointer to a non-const actor 
	animateEntity(data.actorPointer, (*data.stateWindow.first), (*data.stateWindow.second), interpolationScale);
}

template<typename Actor, typename State>
void ALevelController::animateEntity(Actor* actorPointer, const typename State& previousState, const typename State& nextState, float interpolationScale) {
	/*default implementation for entities that aren't spawned/animated yet*/
}

template<typename Each>
void AddToSimFunctor::operator()(const Each& eachStateMap) {
	//identify some related types
	using Entity = typename Each::mapped_type::value_type::Entity;
	using Result = DataMap<Entity>;
	auto& eachSubDestination = std::get<Result>(context->data);

	for (auto& eachEntry : eachStateMap) {
		auto& eachKey = eachEntry.first;
		auto& eachStates = eachEntry.second;
		//there's not much benefit in embedding the differences between parameters for different types here since we'd lose the exact Actor type, so we'll use overloads to handle the manual clarification per-type
		auto eachPointer = context->getOrSpawnActor(eachKey);

		//DO NOT store nullptrs 
		if (eachPointer != nullptr) {
			eachSubDestination.emplace(std::piecewise_construct, std::make_tuple(eachKey), std::make_tuple(eachStates, eachPointer, true));

			//store the pointer for the garbage collector to see
			context->actorPointers.Add(eachPointer);
		}
	}
}

template<typename Each>
void UpdateWindowsFunctor::operator()(Each& eachDataMap) {
	//note: only goes forward for now but can be inverted if need be
	for (auto& eachEntry : eachDataMap) {
		auto& eachSimulationData = eachEntry.second;
		//only bother if it's getting rendered
		if (eachSimulationData.isBeingRendered) {
			auto& eachId = eachEntry.first;
			auto& eachStates = eachSimulationData.states;
			auto& eachWindow = eachSimulationData.stateWindow;

			if (eachWindow.second->time < context->simTime && (eachWindow.second + 1) != eachStates.cend()) {
				//this codesegment updates towards a time in the future compared to the current state for the entity

				//while: the time in state at the end of each window is in the past AND there are states remaining ahead of it (the containing if is the same)
				do {
					//debugging
					
					UE_LOG(LogTemp, Warning, TEXT("Entity %s: moving window to the states %d and %d"), UTF8_TO_TCHAR(eachId.nameForBinaryFile().c_str()), std::distance(eachStates.cbegin(), eachWindow.first), std::distance(eachStates.cbegin(), eachWindow.second));

					//if the ends of the window are the same, instead of sliding both indices forward, want to expand the window by incrementing only the second
					//note that both ends of the window are the same at initialisation ansd as the result of compression once the simulation reaches the end of the alloted time (or, if in reverse, once it reaches the beginning) (see the next comment for an example)
					if (eachWindow.first != eachWindow.second) {
						++eachWindow.first;
					}
					++eachWindow.second;
				} while (eachWindow.second->time < context->simTime && (eachWindow.second + 1) != eachStates.end());

				//if we have reached the end of the simulation, compress the window so the actor sits statically in-place in the final state
				if (eachWindow.second->time < context->simTime) {
					eachWindow.first = eachWindow.second;
				}
			} else if (eachWindow.first->time > context->simTime && eachWindow.first != eachStates.cbegin()) {
				//this codesegment updates towards a time in the past compared to the current state for the entity

				//while: the time in state at the beginning of each window in the future AND there are states remaining behind it (the containing if is the same)
				do {
					//debugging
					UE_LOG(LogTemp, Warning, TEXT("Entity %s: moving window to the states %d and %d"), UTF8_TO_TCHAR(eachId.nameForBinaryFile().c_str()), std::distance(eachStates.cbegin(), eachWindow.first), std::distance(eachStates.cbegin(), eachWindow.second));

					//if the ends of the window are the same, instead of sliding both indices backward, want to expand the window by incrementing only the second
					//note that both ends of the window are the same at initialisation ansd as the result of compression once the simulation reaches the end of the alloted time (or, if in reverse, once it reaches the beginning) (see the next comment for an example)
					if (eachWindow.second != eachWindow.first) {
						--eachWindow.second;
					}
					--eachWindow.first;
				} while (eachWindow.first->time > context->simTime && eachWindow.first != eachStates.cbegin());

				//if we have reached the beginning of the simulation, compress the window so the actor sits statically in-place in the first state
				if (eachWindow.first->time > context->simTime) {
					eachWindow.second = eachWindow.first;
				}
			}
		}
	}
}

template<typename Each>
void AnimateEntitiesFunctor::operator()(Each& eachDataMap) {
	for (auto& eachEntry : eachDataMap) {
		auto& eachSimulationData = eachEntry.second;
		//only bother if it's getting rendered
		if (eachSimulationData.isBeingRendered) {
			auto& eachWindow = eachSimulationData.stateWindow;
			auto& previousState = *(eachWindow.first);
			auto& nextState = *(eachWindow.second);

			//we have to limit the target time in case simTime is outside of the current window (note: this is especially true at the beginning of the simulation/when creation events aren't neccessarily at time 0)
			//TODO: possibly implement consider non-existing that can be used to not render items that don't exist at the current time in the simulation?
			double targetTime = std::max(previousState.time, std::min(nextState.time, context->simTime));

			double interpolationScale;
			if (previousState.time == nextState.time) {
				//if the states are the same, all values between 0 and 1 for the scale would be effectively the same, but the formula would be unable to divide by 0
				interpolationScale = 0;
			} else {
				//determine the interpolation scale using the the formula |current - previous|/|next - previous|
				interpolationScale = (targetTime - previousState.time) / (nextState.time - previousState.time);
			}

			//debug
			auto eachStates = eachSimulationData.states;
			//UE_LOG(LogTemp, Warning, TEXT("Name: %s, Time: %f, state a: %d, state b: %d, typea: %d, typeb: %d, interpolationScale: %f"), UTF8_TO_TCHAR(eachEntry.first.nameForBinaryFile().c_str()), float(context->simTime), std::distance(eachStates.cbegin(), eachWindow.first), std::distance(eachStates.cbegin(), eachWindow.second), previousState.type, nextState.type, interpolationScale);

			context->animateEntity(eachSimulationData, interpolationScale);
		}
	}
}

template<typename Each>
void FindSimTimeBoundsFunctor::operator()(const Each& eachDataMap) {
	for (auto& eachEntry : eachDataMap) {
		for (auto& eachState : eachEntry.second.states) {
			if (eachState.time < context->simStartTime) {
				context->simStartTime = eachState.time;
			}
			if (eachState.time > context->simEndTime) {
				context->simEndTime = eachState.time;
			}
		}
	}
}

template<typename Each>
void ClearDataFunctor::operator()(Each& eachStateMap) {
	eachStateMap.clear();
}

template<typename Each>
inline void StringifyEventsFunctor::operator()(Each & eachDataMap)
{
	std::stringstream eachResultBuilder;
	for (auto& eachEntry : eachDataMap) {
		auto& eachId = eachEntry.first;
		for (auto& eachState : eachEntry.second.states) {

			//TODO: REPLACE WITH SOMETHING LIKE StateTraits<typename Each::key_type::Entity>::displayFriendlyStringFor(eachState) (note: this method is not yet implemented or even declared)
			eachResultBuilder.str("");
			//TODO: IMPLEMENT A TYPEDEF OR SIMILAR THAT CAN GET FROM Entity CLASSES TO THE STATETYPEDECODER e.g. std::function<std::string(StackerStateType)>Stacker::stateTypeDecoder(StackerStateType type)
			eachResultBuilder << "Entity " << eachId.nameForBinaryFile() << ": Current State: " << int(eachState.type);
			interimResult.emplace_back(eachState.time, eachResultBuilder.str());
		}
	}
}
