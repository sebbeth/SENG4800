// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelController.h"
#include "StackerReclaimer.h"
#include "ShipLoader.h"
#include "Ship.h"
#include "CoalStack.h"
#include "ConveyorBelt.h"
#include "Train.h"
#include "data/env_config.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include <algorithm>
#include <cstdlib>
#include <fstream>

#include "data/loadData.h"

using namespace std;

int mock_state;
float mock_level;
std::tuple<TerminalId, std::string, int> padLengths;
std::tuple<TerminalId, std::string, int> trackLengths;

std::string lastActorId;
bool playHasBeenClickedTrains = false;


// Sets default values
ALevelController::ALevelController() : addToSimFunctor(this), updateWindowsFunctor(this), animateEntitiesFunctor(this), findSimTimeBoundsFunctor(this), clearDataFunctor(this), stringifyEventsFunctor(this), simTime(0), simStartTime(0), simEndTime(0), speed(1), isPlaying(false) {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALevelController::BeginPlay()
{
	Super::BeginPlay();
	//loadXMLData(UTF8_TO_TCHAR(XML_PATH.c_str()));
}

// Called every frame; not very interesting; see template<typename Each> void AnimateEntitiesFunctor::operator()(const Each& eachDataMap) in the header file
void ALevelController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isPlaying) {
		moveSimTime(DeltaTime * speed);
		forEachInTuple(data, animateEntitiesFunctor);
	}
	forEachInTuple(data, animateEntitiesFunctor);
}

AddToSimFunctor::AddToSimFunctor(): context(nullptr) {
}

AddToSimFunctor::AddToSimFunctor(ALevelController* context): context(context) {
}

UpdateWindowsFunctor::UpdateWindowsFunctor() : context(nullptr) {
}

UpdateWindowsFunctor::UpdateWindowsFunctor(ALevelController* context): context(context) {
}

AnimateEntitiesFunctor::AnimateEntitiesFunctor() : context(nullptr) {
}

AnimateEntitiesFunctor::AnimateEntitiesFunctor(ALevelController* context) : context(context) {
}

FindSimTimeBoundsFunctor::FindSimTimeBoundsFunctor() : context(nullptr) {
}

FindSimTimeBoundsFunctor::FindSimTimeBoundsFunctor(ALevelController* context): context(context) {
}

ClearDataFunctor::ClearDataFunctor() : context(nullptr) {
}

ClearDataFunctor::ClearDataFunctor(ALevelController* context): context(context) {
}

StringifyEventsFunctor::StringifyEventsFunctor()
{
}

StringifyEventsFunctor::StringifyEventsFunctor(ALevelController * context) : context(context) {
}

void FindSimTimeBoundsFunctor::operator()() {
	context->simStartTime = std::numeric_limits<float>::infinity();
	context->simEndTime = -std::numeric_limits<float>::infinity();
	auto& thisRef = *this;
	forEachInTuple(context->data, thisRef);
	if (std::isinf(context->simStartTime) || std::isinf(context->simEndTime)) {
		context->simStartTime = 0;
		context->simEndTime = 0;
	}
}

void ClearDataFunctor::operator()() {
	auto& thisRef = *this;
	forEachInTuple(context->data, thisRef);
	context->actorPointers.Empty();
}

TArray<FString> StringifyEventsFunctor::operator()() {
	interimResult.clear();
	forEachInTuple(context->data, (*this));
	std::sort(interimResult.begin(), interimResult.end());
	TArray<FString> result;
	for (auto eachPair : interimResult) {
		result.Add(UTF8_TO_TCHAR(eachPair.second.c_str()));
	}
	return result;
}

bool ALevelController::loadXMLData(const  FString& srcPath) {
	auto stateResultPair = ::loadXMLData(TCHAR_TO_UTF8(*srcPath));

	//only do the rest if the data-loading was successful
	if (stateResultPair.second) {
		clearDataFunctor();

		//add the new data in
		auto& states = stateResultPair.first;
		forEachInTuple(states, addToSimFunctor);
		findSimTimeBoundsFunctor();
	}

	return stateResultPair.second;
}

TArray<FString> ALevelController::getEventMessages() {
	return stringifyEventsFunctor();
}

float ALevelController::getSimTime() {
	return simTime;
}

float ALevelController::getSimStart()
{
	return simStartTime;
}

float ALevelController::getSimEndTime()
{
	return simEndTime;
}

void ALevelController::setSimTime(float absoluteTime) {
	simTime = std::max(0.0, std::min(simEndTime, (double)absoluteTime));
	forEachInTuple(data, updateWindowsFunctor);
}

void ALevelController::moveSimTime(float deltaTime) {
	setSimTime(simTime + deltaTime);
}

float ALevelController::getPlaySpeed() {
	return speed;
}

void ALevelController::setPlaySpeed(float speed) {
	this->speed = speed;
}

bool ALevelController::getPlayState() {
	return isPlaying;
}

void ALevelController::setPlayState(bool isPlaying) {
	this->isPlaying = isPlaying;
}

/*

*/
void ALevelController::stackCoal(int stackerId) {
	setCoalStackingState(stackerId, 2);
}



void ALevelController::stopStackingCoal(int stackerId) {
	setCoalStackingState(stackerId, 1);

}

/*
Helper function used by addCoal and stopAddingCoal to set materials for Actors
*/
void ALevelController::setCoalStackingState(int stackerId, int state) {
	if (stackerReclaimers[stackerId] == NULL) {
		return; // Return if given invalid input
	}
	stackerReclaimers[stackerId]->setMaterial(state); // Set the material of the stacker
    // Now we need to figure out which conveyor belts need to be lit
	switch (stackerId)
	{
	case 0:
		conveyorBelts[0]->setMaterial(state);
		conveyorBelts[1]->setMaterial(state);
		conveyorBelts[6]->setMaterial(state);
		conveyorBelts[11]->setMaterial(state);
		break;
	case 1:
		conveyorBelts[0]->setMaterial(state);
		conveyorBelts[1]->setMaterial(state);
		conveyorBelts[5]->setMaterial(state);
		conveyorBelts[10]->setMaterial(state);
		break;
	case 2:
		conveyorBelts[0]->setMaterial(state);
		conveyorBelts[1]->setMaterial(state);
		conveyorBelts[4]->setMaterial(state);
		conveyorBelts[9]->setMaterial(state);
		break;
	case 3:
		conveyorBelts[0]->setMaterial(state);
		conveyorBelts[1]->setMaterial(state);
		conveyorBelts[3]->setMaterial(state);
		conveyorBelts[2]->setMaterial(state);
		break;
	default:
		break;
	}
}


/*
	Terminal ID - the ids will link to a terminal (KCT, NCIG, CCT), the pad will also have an ID value.
*/
int ALevelController::getPadLength(TerminalId terminal, const int& padId) {
	// KCT Terminal Pads.
	
	switch (terminal) {
		case TerminalId::KCT:
			switch(padId) {
				case 0: // Pad a
					return 2285;
				case 1: // pad b
					return 2180;
				case 2: //pad c
					return 2155;
				case 3: //pad d
					return 2315;
					
			}
		case TerminalId::NCT:
			switch (padId) {
				case 0: // Pad a
					return 1055;
				case 1: // pad bc
					return 1100;
				case 2: //pad de
					return 1113;
				case 3: //pad fg
					return 1160;
				case 4: // pad H
					return 1173;
			}
		case TerminalId::CCT:
			switch (padId) { // alls pads are defined the same length
				case 0:
				case 1:
				case 2:
				case 3:
					return 770;
			}
		default: 
			return -1;
	}
}
/*
*/
int ALevelController::getTrackLength(TerminalId terminal, const int& trackId) {

	switch (terminal) {
	case TerminalId::KCT:
		switch (trackId) {
		case 0: // Track a
		case 1: // Track b
		case 2: // Track c
		case 3: // Track d
		case 4: // Track e
			return 2315;
		}
	case TerminalId::NCT:
		switch (trackId) {
		case 0: // Track a
			return 1100;
		case 1: // Track b
			return 1113;
		case 2: // Track c
			return 1160;
		case 3: // Track d
			return 1173;
		}
	case TerminalId::CCT:
		switch (trackId) { // alls Track are defined the same length
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			return 770;
		}
	default:
		return -1;
	}
}
/*

*/
void ALevelController::reclaimCoal(int stackerId, int loaderId) {
	setCoalReclaimingState(stackerId, loaderId, 0);
}


void ALevelController::stopReclaimingCoal(int stackerId, int loaderId) {
	setCoalReclaimingState(stackerId, loaderId, 1);

}

void ALevelController::setCoalReclaimingState(int stackerId, int loaderId, int state) {

//	if ((stackerReclaimers[stackerId] == NULL) || (shipLoaders[loaderId] == NULL) ) {
//		return; // Return if given invalid input
	//}

	stackerReclaimers[stackerId]->setMaterial(state); // Set the material of the stacker
	//TODO loaders able to change material

	// Now set the material for the terminal conveyor belts
	switch (stackerId)
	{
	case 0:
		conveyorBelts[6]->setMaterial(state);
		break;
	case 1:
		conveyorBelts[5]->setMaterial(state);
		break;
	case 2:
		conveyorBelts[4]->setMaterial(state);
		conveyorBelts[7]->setMaterial(state);
		break;
	case 3:
		conveyorBelts[3]->setMaterial(state);
		conveyorBelts[8]->setMaterial(state);
		break;
	default:
		break;
	}

	// Now set the material for the loader conveyor belts
	switch (loaderId)
	{
	case 0:
		conveyorBelts[12]->setMaterial(state);
		conveyorBelts[15]->setMaterial(state);\
		break;
	case 1:
		conveyorBelts[13]->setMaterial(state);
		conveyorBelts[14]->setMaterial(state);
		break;
	default:
		break;
	}



}



/*  *** Actor spawn functions *** 

Each function
	instantiates a new actor, 
	sets any attributes required (position, ID, etc)
	adds the actor to the appropriate actor array
	and returns the actor.


NOTE: there is no need to add the returned actor to an array manually, it is added to the appropriate array here.

example usage: 
	spawnACoalStack("CS_1", NCT_pads[0]->GetActorLocation(), NCT_pads[0]->GetActorRotation(), coal_stack_blueprint);
*/


AStackerReclaimer * ALevelController::spawnAStackerReclaimer(FString id, FVector railStart, FVector railEnd, TSubclassOf<class AStackerReclaimer> blueprint) {
	
	UWorld* world = GetWorld();
	if (world) {
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		AStackerReclaimer *actor = world->SpawnActor<AStackerReclaimer>(blueprint, railStart, FRotator(0.0f, 0.0f, 0.0f), spawnParams);
		actor->trackNodeA = railStart;
		actor->trackNodeB = railEnd;
		actor->id = id;
		stackerReclaimers.Add(actor);
		return actor;
	}
	return NULL;
}


AShipLoader * ALevelController::spawnAShipLoader(FString id, FVector railStart, FVector railEnd, TSubclassOf<class AShipLoader> blueprint) {

	UWorld* world = GetWorld();
	if (world) {
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		AShipLoader *actor = world->SpawnActor<AShipLoader>(blueprint, railStart, FRotator(0.0f, 0.0f, 0.0f), spawnParams);
		actor->trackNodeA = railStart;
		actor->trackNodeB = railEnd;
		shipLoaders.Add(actor);
		return actor;
	}
	return NULL;
}


AShip * ALevelController::spawnAShip(FString id, FVector position, FRotator rotator, TSubclassOf<class AShip> blueprint) {
	
	UWorld* world = GetWorld();
	if (world) {
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		AShip *actor = world->SpawnActor<AShip>(blueprint, position, rotator, spawnParams);
		ships.Add(actor);
		return actor;
	}
	return NULL;
}



ACoalStack * ALevelController::spawnACoalStack(FString id, FVector position, FRotator rotator, TSubclassOf<class ACoalStack> blueprint) {
	UWorld* world = GetWorld();
	if (world) {
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		ACoalStack *actor = world->SpawnActor<ACoalStack>(blueprint, position, rotator, spawnParams);
		coalStacks.Add(actor);
		return actor;
	}
	return NULL;
}


AConveyorBelt * ALevelController::spawnAConveyorBelt(FString id, FVector position, FRotator rotator, TSubclassOf<class AConveyorBelt> blueprint) {
	UWorld* world = GetWorld();
	if (world) {
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		AConveyorBelt *actor = world->SpawnActor<AConveyorBelt>(blueprint, position, rotator, spawnParams);
		conveyorBelts.Add(actor);
		return actor;
	}
	return NULL;
}

ATrain * ALevelController::spawnATrain(FString id, FVector position, FRotator rotator, TSubclassOf<class ATrain> blueprint) {
	UWorld* world = GetWorld();
	if (world) {
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		ATrain *actor = world->SpawnActor<ATrain>(blueprint, position, rotator, spawnParams);
		actor->id = id;
		trains.Add(actor);
		return actor;
	}
	return NULL;
}

AStackerReclaimer* ALevelController::getOrSpawnActor(const StackerReclaimer::Id& id) {
	static std::string nct_names[4] = { "SR01", "SR02", "SR03", "SR04" };
	if (id.terminal == TerminalId::NCT) {
		for (int i = 0; i < 4; ++i) {
			if (id.name == nct_names[i]) {
				return spawnAStackerReclaimer(UTF8_TO_TCHAR(id.nameForBinaryFile().c_str()), NCT_SR_rails_start[i]->GetActorLocation(), NCT_SR_rails_end[i]->GetActorLocation(), largeSR_blueprint);
			}
		}
	}
	return nullptr;
}

void ALevelController::animateEntity(AStackerReclaimer* actorPointer, const StackerReclaimerState& previousState, const StackerReclaimerState& nextState, float interpolationScale) {

	//TODO: ENCODE THE LENGTH OF THE RAILS AS FAR AS THE INPUT DATA IS CONCERNED SOMEWHERE
	//start temporary hack: assume the end is the max value in the current set of states
	StackerReclaimer::Id targetId = previousState.id;
	float minPosition = 0;
	float maxPosition = 0;
	auto& theMap = std::get<DataMap<StackerReclaimer>>(data);
	auto targetIterator = theMap.find(targetId);
	if (targetIterator != theMap.end()) {
		for (auto eachState : (*targetIterator).second.states) {
			if (eachState.position > maxPosition) {
				maxPosition = eachState.position;
			}
		}
	}
	//end of temporary hack
	
	//calculate the absolute position of the machine (along it's rail) by interpolating the previous and next positions
	//this idea came from vector mathmemathics, with 1d vectors (efficively scalars) is this case; the formula is: previous+(next - previous)*scale;
	float positionInterpolated = previousState.position + (nextState.position - previousState.position)*interpolationScale;

	//convert the absolute position to a scale between 0.0 and 1.0 which can then be used with the vectors placed manually in the editor.
	float positionScale = (positionInterpolated - minPosition) / (maxPosition - minPosition);

	//update the actor position
	actorPointer->setPosition(positionScale);
	//TODO: ADD TURNING CONSIDERATIONS


	//UE_LOG(LogTemp, Warning, TEXT("timeA: %f, timeb: %f positiona: %f, positionb: %f, positionInterpolated: %f Position scale: %f"), float(previousState.time), float(nextState.time), float(previousState.position), float(nextState.position), float(positionInterpolated), float(positionScale));
}

ATrain* ALevelController::getOrSpawnActor(const TrainMovement::Id& id)
{
	//stub
	//UE_LOG(LogTemp, Warning, TEXT("Added a Train found a train id %s "), UTF8_TO_TCHAR(id.nameForBinaryFile().c_str()));
   return spawnATrain(UTF8_TO_TCHAR(id.nameForBinaryFile().c_str()), trainTracks[0]->Spline->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World),
		trainTracks[0]->Spline->GetRotationAtSplinePoint(0, ESplineCoordinateSpace::World), train_locomotive_blueprint);
	
}


/*//change back to other method check out actorPointer
void ALevelController::animateEntity(const SimulationData<TrainMovement>& data, float interpolationScale)
{
	//interpolationScale is how far towards nextState the current time is from previousState. 
	//The scale is from 0.0 to 1.0: 
	//at 0.0 the current time is exactly that of previousState
	//at 1.0 the current time is exactly that of nextState

	//interpolationScale is always 0, not sure what thats suppose to mean, using either animateEntity method its always 0
	if (!setupTrainData)
	{
		
		//for ( std::vector<TrainMovementState>::const_iterator it = data.states.cbegin(); it != data.states.cend(); it++)//all train movement states
		for(auto eachState : data.states)
		{
		
			//UE_LOG(LogTemp, Warning, TEXT("eachState id %s  "), UTF8_TO_TCHAR(eachState.id.name.c_str()) );

			if (eachState.type == TrainMovementStateType::EnteringTrack)
			{

				//UE_LOG(LogTemp, Warning, TEXT("Entering Track state on eachState id %s , trackId %s"), UTF8_TO_TCHAR(eachState.id.name.c_str()), UTF8_TO_TCHAR(eachState.trackID.c_str()));
				for (auto eachTrack : (trainTracks))
				{
					if (eachState.trackID == std::string(TCHAR_TO_UTF8(*eachTrack->id)))
					{
						UE_LOG(LogTemp, Warning, TEXT("ENTERINGTRACK train id: %s , track id from data: %s , my Track id: %s , interpolationScale %f"), UTF8_TO_TCHAR(eachState.id.name.c_str()), UTF8_TO_TCHAR(eachState.trackID.c_str()), *FString(eachTrack->id), float(interpolationScale) );

					}
				}

			}
			else if (eachState.type == TrainMovementStateType::InJunction)
			{
				for (auto eachTrack : (trainTracks))
				{
					if (eachState.trackID == std::string(TCHAR_TO_UTF8(*eachTrack->id)))
					{
						UE_LOG(LogTemp, Warning, TEXT("INJUNCTION train id: %s , track id from data: %s , my Track id: %s , interpolationScale %f"), UTF8_TO_TCHAR(eachState.id.name.c_str()), UTF8_TO_TCHAR(eachState.trackID.c_str()), *FString(eachTrack->id), float(interpolationScale) );

					}
				}
			}
		// // should no longer be any, use take that with a grain of salt but the state transitions have been modified
		//else if (eachState.type == TrainMovementStateType::Invalid)
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("Invalid state on eachState id %s , trackId %s"), UTF8_TO_TCHAR(eachState.id.name.c_str()), UTF8_TO_TCHAR(eachState.trackID.c_str()) );
		//}
		//

		
		}


	}
	else
	{
		//animate trains
		//UE_LOG(LogTemp, Warning, TEXT("interpolationScale %f"), float(interpolationScale));
	}

	if (trainsCount == trains.Num())
	{
		//STOP we reached the first ever seen id so we have looked at every train's event states at least once!
		setupTrainData = true;
	}
	if (!setupTrainData)
	{
		trainsCount++;
	}

	

}
*/

		// old code
void ALevelController::animateEntity(ATrain* actorPointer, const TrainMovementState& previousState, const TrainMovementState& nextState, float interpolationScale)
{
	//previous and next seem to be both pointing to the same state , tested with output  ln: 538
	//UE_LOG(LogTemp, Warning, TEXT("previousState id %s , nextState id %s "), UTF8_TO_TCHAR(previousState.id.name.c_str()), UTF8_TO_TCHAR(nextState.id.name.c_str()));
	
	
	if (isPlaying)
	{
		playHasBeenClickedTrains = true;
	//ps = previousState
	//ns = nextState
	//et = EnteringTrack 
	//ijn = InJunction

	//ps et ns et
	//ps et ns ijn  
	//ps jn ns ijn
	//ps jn ns et



		if (previousState.type == TrainMovementStateType::EnteringTrack)
		{
			if (nextState.type == TrainMovementStateType::EnteringTrack)
			{
				//both point to the same state
				UE_LOG(LogTemp, Warning, TEXT("ENTERINGTRACK previousState, ENTERINGTRACK nextState, train id : %s, track id from data : %s , interpolationScale %f "), UTF8_TO_TCHAR(previousState.id.name.c_str()), UTF8_TO_TCHAR(previousState.trackID.c_str()), float(interpolationScale));
			}
			else if (nextState.type == TrainMovementStateType::InJunction)
			{
				// next state the train is leaving this track iterate for the track in previous state as we haven't left the track until interpolationScale == 1.0
				for (auto eachTrack : trainTracks)
				{
	
					if (previousState.trackID == std::string(TCHAR_TO_UTF8(*eachTrack->id)))
					{
						//UE_LOG(LogTemp, Warning, TEXT("ENTERINGTRACK train id: %s , track id from data: %s , my Track id: %s"), UTF8_TO_TCHAR(previousState.id.name.c_str()), UTF8_TO_TCHAR(previousState.trackID.c_str()), *FString(eachTrack->id) );
	
						//train is at start of this track?
						lastActorId = previousState.id.name;
						UE_LOG(LogTemp, Warning, TEXT("ENTERINGTRACK previousState, INJUNCTION nextState, train id: %s , track id from data: %s , my Track id: %s , interpolationScale %f "), UTF8_TO_TCHAR(previousState.id.name.c_str()), UTF8_TO_TCHAR(previousState.trackID.c_str()), *FString(eachTrack->id), float(interpolationScale));
						
						lastActorId = previousState.id.name;
						
						float distance = eachTrack->Spline->GetSplineLength() * interpolationScale;
						auto makeTransform = FTransform(eachTrack->Spline->GetRotationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World),
							eachTrack->Spline->GetLocationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World),
							FVector(1.0f, 1.0f, 1.0f));
	
						actorPointer->SetActorTransform(makeTransform);
					}
				}
	
			}
			//UE_LOG(LogTemp, Warning, TEXT("Entering Track state on previousState id %s "), UTF8_TO_TCHAR(previousState.id.name.c_str()) );
	
		}
		else if (previousState.type == TrainMovementStateType::InJunction) //current trains head left the track
		{
			if (nextState.type == TrainMovementStateType::InJunction)
			{
				//both point to the same state
			   // UE_LOG(LogTemp, Warning, TEXT("INJUNCTION nextState, INJUNCTION previousState, train id : %s, track id from data : %s , interpolationScale %f "), UTF8_TO_TCHAR(previousState.id.name.c_str()), UTF8_TO_TCHAR(previousState.trackID.c_str()), float(interpolationScale));
				// INJUNCTION nextState, INJUNCTION previousState, train id : train40, track id from data : trk_KCT_Initial , interpolationScale 0.000000  for every train id why?
				
			}
			else if (nextState.type == TrainMovementStateType::EnteringTrack)
			{
				// next state the train is entering nextState's track iterate for the track in previousState as we haven't left into interpolationScale ==  1.0 therefore we must be in previousState's track
				for (auto eachTrack : trainTracks)
				{
					//UE_LOG(LogTemp, Warning, TEXT("InJunction previousState train id: %s , track id from data: %s , my Track id: %s , interpolationScale %f "), UTF8_TO_TCHAR(previousState.id.name.c_str()), UTF8_TO_TCHAR(previousState.trackID.c_str()), *FString(eachTrack->id), float(interpolationScale));
					if (previousState.trackID == std::string(TCHAR_TO_UTF8(*eachTrack->id)))
					{
						//UE_LOG(LogTemp, Warning, TEXT("ENTERINGTRACK train id: %s , track id from data: %s , my Track id: %s"), UTF8_TO_TCHAR(previousState.id.name.c_str()), UTF8_TO_TCHAR(previousState.trackID.c_str()), *FString(eachTrack->id) );
						UE_LOG(LogTemp, Warning, TEXT("INJUNCTION previousState, ENTERINGTRACK nextState, train id: %s , track id from data: %s , my Track id: %s , interpolationScale %f "), UTF8_TO_TCHAR(previousState.id.name.c_str()), UTF8_TO_TCHAR(previousState.trackID.c_str()), *FString(eachTrack->id), float(interpolationScale));
						
						lastActorId = previousState.id.name;
						
						float distance = eachTrack->Spline->GetSplineLength() * interpolationScale;
						auto makeTransform = FTransform(eachTrack->Spline->GetRotationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World),
							eachTrack->Spline->GetLocationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World),
							FVector(1.0f, 1.0f, 1.0f));
	
						actorPointer->SetActorTransform(makeTransform);
	
						//train moves to end of current traintrack?
					}
				}
			}
			//UE_LOG(LogTemp, Warning, TEXT("InJunction state on previousState id %s "), UTF8_TO_TCHAR(previousState.id.name.c_str()) );
	
	
		}
		else
		{
			if (nextState.type == TrainMovementStateType::EnteringTrack)
			{
				if (previousState.type == TrainMovementStateType::EnteringTrack)
				{
					//both point to the same state
					UE_LOG(LogTemp, Warning, TEXT("ENTERINGTRACK nextState, ENTERINGTRACK previousState, train id : %s, track id from data : %s , interpolationScale %f "), UTF8_TO_TCHAR(previousState.id.name.c_str()), UTF8_TO_TCHAR(previousState.trackID.c_str()), float(interpolationScale));
				}
				else if (previousState.type == TrainMovementStateType::InJunction)
				{
					// next state the train is leaving this track iterate for the track in previous state as we haven't left the track until interpolationScale == 1.0
					for (auto eachTrack : trainTracks)
					{
	
						if (previousState.trackID == std::string(TCHAR_TO_UTF8(*eachTrack->id)))
						{
							//UE_LOG(LogTemp, Warning, TEXT("ENTERINGTRACK train id: %s , track id from data: %s , my Track id: %s"), UTF8_TO_TCHAR(previousState.id.name.c_str()), UTF8_TO_TCHAR(previousState.trackID.c_str()), *FString(eachTrack->id) );
	
							//train is at start of this track?
							UE_LOG(LogTemp, Warning, TEXT("ENTERINGTRACK nextState, INJUNCTION previousState, train id: %s , track id from data: %s , my Track id: %s , interpolationScale %f "), UTF8_TO_TCHAR(previousState.id.name.c_str()), UTF8_TO_TCHAR(previousState.trackID.c_str()), *FString(eachTrack->id), float(interpolationScale));
							
							lastActorId = previousState.id.name;
							
							float distance = eachTrack->Spline->GetSplineLength() * interpolationScale;
	
							auto makeTransform = FTransform(eachTrack->Spline->GetRotationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World),
								eachTrack->Spline->GetLocationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World),
								FVector(1.0f, 1.0f, 1.0f));
	
							actorPointer->SetActorTransform(makeTransform);
						}
					}
	
				}
				//UE_LOG(LogTemp, Warning, TEXT("Entering Track state on previousState id %s "), UTF8_TO_TCHAR(previousState.id.name.c_str()) );
	
	
			}
			else if (nextState.type == TrainMovementStateType::InJunction) //current trains head left the track
			{
				if (previousState.type == TrainMovementStateType::InJunction)
				{
					//both point to the same state
				   // UE_LOG(LogTemp, Warning, TEXT("INJUNCTION nextState, INJUNCTION previousState, train id : %s, track id from data : %s , interpolationScale %f "), UTF8_TO_TCHAR(previousState.id.name.c_str()), UTF8_TO_TCHAR(previousState.trackID.c_str()), float(interpolationScale));
					// INJUNCTION nextState, INJUNCTION previousState, train id : train40, track id from data : trk_KCT_Initial , interpolationScale 0.000000  for every train id why?
				}
				else if (previousState.type == TrainMovementStateType::EnteringTrack)
				{
					// next state the train is entering nextState's track iterate for the track in previousState as we haven't left into interpolationScale ==  1.0 therefore we must be in previousState's track
					for (auto eachTrack : trainTracks)
					{
						//UE_LOG(LogTemp, Warning, TEXT("InJunction previousState train id: %s , track id from data: %s , my Track id: %s , interpolationScale %f "), UTF8_TO_TCHAR(previousState.id.name.c_str()), UTF8_TO_TCHAR(previousState.trackID.c_str()), *FString(eachTrack->id), float(interpolationScale));
						if (previousState.trackID == std::string(TCHAR_TO_UTF8(*eachTrack->id)))
						{
							//UE_LOG(LogTemp, Warning, TEXT("ENTERINGTRACK train id: %s , track id from data: %s , my Track id: %s"), UTF8_TO_TCHAR(previousState.id.name.c_str()), UTF8_TO_TCHAR(previousState.trackID.c_str()), *FString(eachTrack->id) );
							UE_LOG(LogTemp, Warning, TEXT("INJUNCTION nextState, ENTERINGTRACK previousState, train id: %s , track id from data: %s , my Track id: %s , interpolationScale %f "), UTF8_TO_TCHAR(previousState.id.name.c_str()), UTF8_TO_TCHAR(previousState.trackID.c_str()), *FString(eachTrack->id), float(interpolationScale));
							float distance = eachTrack->Spline->GetSplineLength() * interpolationScale;
	
							lastActorId = previousState.id.name;

							auto makeTransform = FTransform(eachTrack->Spline->GetRotationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World),
								eachTrack->Spline->GetLocationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World),
								FVector(1.0f, 1.0f, 1.0f));
	
							actorPointer->SetActorTransform(makeTransform);
	
							//train moves to end of current traintrack?
						}
					}
				}
				//UE_LOG(LogTemp, Warning, TEXT("InJunction state on previousState id %s "), UTF8_TO_TCHAR(previousState.id.name.c_str()) );
			}
		}
	 

		if (lastActorId == std::string(TCHAR_TO_UTF8(*actorPointer->id))) //this may fire when simulation is left to run, not sure why as "isPlaying" should be false
																		  //from that point however it appears it continues to tick until stop or pause is clicked
		{
			for (auto eachTrack : trainTracks)
			{

				if (previousState.trackID == std::string(TCHAR_TO_UTF8(*eachTrack->id)))
				{
					//UE_LOG(LogTemp, Warning, TEXT("ENTERINGTRACK train id: %s , track id from data: %s , my Track id: %s"), UTF8_TO_TCHAR(previousState.id.name.c_str()), UTF8_TO_TCHAR(previousState.trackID.c_str()), *FString(eachTrack->id) );

					//train is at start of this track?
					lastActorId = previousState.id.name;
					UE_LOG(LogTemp, Warning, TEXT("INJUNCTION previousState, INJUNCTION nextState, train id: %s , track id from data: %s , my Track id: %s , interpolationScale %f "), UTF8_TO_TCHAR(previousState.id.name.c_str()), UTF8_TO_TCHAR(previousState.trackID.c_str()), *FString(eachTrack->id), float(interpolationScale));

					lastActorId = previousState.id.name;

					float distance = eachTrack->Spline->GetSplineLength() * interpolationScale;
					auto makeTransform = FTransform(eachTrack->Spline->GetRotationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World),
						eachTrack->Spline->GetLocationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World),
						FVector(1.0f, 1.0f, 1.0f));

					actorPointer->SetActorTransform(makeTransform);
				}
			}
		}
	}//end of isPlaying check
	else if (simTime == 0.0f && playHasBeenClickedTrains == true)//if stopped (i don't think i can check for this though?????)
	{
		// reset actors to hidden track
		UE_LOG(LogTemp, Warning, TEXT("simTime is 0.0f : %f "), float(simTime) );

		auto makeTransform = FTransform(trainTracks[0]->Spline->GetRotationAtSplinePoint(0, ESplineCoordinateSpace::World),
			trainTracks[0]->Spline->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World),
			FVector(1.0f, 1.0f, 1.0f));

		for (auto eachTrain : trains)
		{
			eachTrain->SetActorTransform(makeTransform);
		}
		playHasBeenClickedTrains = false;
		
	 }
}