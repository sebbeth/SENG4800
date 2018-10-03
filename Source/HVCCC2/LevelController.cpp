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
#include <string>

#include "data/loadData.h"

using namespace std;

int mock_state;
float mock_level;
std::tuple<TerminalId, std::string, int> padLengths;
std::tuple<TerminalId, std::string, int> trackLengths;

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



int ALevelController::getShipLoaderTrackLength(TerminalId terminal) {

	switch (terminal) {
	case TerminalId::KCT:
		return 1040;
	case TerminalId::NCT:
		return 1040;
	case TerminalId::CCT:
		return 750;
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
		conveyorBelts[15]->setMaterial(state);
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
	spawnACoalStack("CS_1", NCT_pads_start[0]->GetActorLocation(), NCT_pads_start[0]->GetActorRotation(), coal_stack_blueprint);
*/


AStackerReclaimer * ALevelController::spawnAStackerReclaimer(FString id, int trackId, FVector railStart, FVector railEnd, TSubclassOf<class AStackerReclaimer> blueprint) {
	
	UWorld* world = GetWorld();
	if (world) {
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		AStackerReclaimer *actor = world->SpawnActor<AStackerReclaimer>(blueprint, railStart, FRotator(0.0f, 0.0f, 0.0f), spawnParams);
		actor->trackNodeA = railStart;
		actor->trackNodeB = railEnd;
		actor->id = id;
		actor->trackId = trackId;
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
		actor->id = id;
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
		actor->id = id;
		ships.Add(actor);
		return actor;
	}
	return NULL;
}





ACoalStack * ALevelController::spawnACoalStack(FString id, FVector position, FRotator rotator, float width, TSubclassOf<class ACoalStack> blueprint) {
	UWorld* world = GetWorld();
	if (world) {
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		ACoalStack *actor = world->SpawnActor<ACoalStack>(blueprint, position, rotator, spawnParams);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *id);
		actor->id = id;
		actor->setWidth(width);
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
		actor->id = id;
		conveyorBelts.Add(actor);
		return actor;
	}
	return NULL;
}

ATrain * ALevelController::spawnATrain(FString id, FVector position, TSubclassOf<class ATrain> blueprint) {
	UWorld* world = GetWorld();
	if (world) {
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		ATrain *actor = world->SpawnActor<ATrain>(blueprint, position, FRotator(0,0,0), spawnParams);
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
				return spawnAStackerReclaimer(UTF8_TO_TCHAR(id.nameForBinaryFile().c_str()),i, NCT_SR_rails_start[i]->GetActorLocation(), NCT_SR_rails_end[i]->GetActorLocation(), largeSR_blueprint);
			}
		}
	}
	return nullptr;
}



AShip* ALevelController::getOrSpawnActor(const Vessel::Id& id) {
	static std::string nct_names[4] = { "SHIP:1", "SHIP:2", "SHIP:3", "SHIP:4" };
	FString ff = UTF8_TO_TCHAR(id.name.c_str());
	UE_LOG(LogTemp, Warning, TEXT("SHIP:%s"), *ff);
	//if (id.terminal == TerminalId::NCT) {
		//for (int i = 0; i < 4; ++i) {
		//	if (id.name == nct_names[i]) {
				return spawnAShip(UTF8_TO_TCHAR(id.nameForBinaryFile().c_str()), NCT_berths[0]->GetActorLocation(), NCT_berths[0]->GetActorRotation(), ship_blueprint);
		//	}
		//}
	//}
	return nullptr;
}


ACoalStack* ALevelController::getOrSpawnActor(const Stockpile::Id& id) {
	if (id.terminal == TerminalId::NCT) {
	for (int i = 0; i < 4; ++i) {
		// NOTE actors are being spawned to 0,0,0 rather then being spawned and then made invisible
			return spawnACoalStack(UTF8_TO_TCHAR(id.nameForBinaryFile().c_str()), FVector(0,0,0), NCT_pads_start[i]->GetActorRotation(), NCT_pads_start[i]->GetActorScale3D().X, coal_stack_blueprint);
	}
	}
	return nullptr;
}

AShipLoader* ALevelController::getOrSpawnActor(const Shiploader::Id& id) {
	static std::string nct_names[2] = { "SL01", "SL02"};
	if (id.terminal == TerminalId::NCT) {
		for (int i = 0; i < 2; ++i) {
			if (id.name == nct_names[i]) {
				return spawnAShipLoader(UTF8_TO_TCHAR(id.nameForBinaryFile().c_str()), NCT_loader_rails_start[i]->GetActorLocation(), NCT_loader_rails_end[i]->GetActorLocation(), ship_loader_blueprint);
			}
		}
	}
	return nullptr;
}


void ALevelController::animateEntity(AStackerReclaimer* actorPointer, const StackerReclaimerState& previousState, const StackerReclaimerState& nextState, float interpolationScale) {

	StackerReclaimer::Id targetId = previousState.id;
	float minPosition = 0;
	//TODO, assign the correct track length, not just the 0'th one
	float maxPosition = (float)getTrackLength(targetId.terminal, actorPointer->trackId);
	//calculate the absolute position of the machine (along it's rail) by interpolating the previous and next positions
	//this idea came from vector mathmemathics, with 1d vectors (efficively scalars) is this case; the formula is: previous+(next - previous)*scale;
	float positionInterpolated = previousState.position + (nextState.position - previousState.position)*interpolationScale;
	//convert the absolute position to a scale between 0.0 and 1.0 which can then be used with the vectors placed manually in the editor.
	float positionScale = (positionInterpolated - minPosition) / (maxPosition - minPosition);
	//update the actor position
	actorPointer->setPosition(positionScale);
	//TODO: ADD TURNING CONSIDERATIONS
		
	switch (previousState.type)
	{
	case StackerReclaimerStateType::Moving:
		actorPointer->setRotation(0.0f); // If the SR is moving, set it's arm to forward
		break;
	case StackerReclaimerStateType::WorkingStack: 
		// If the SR is Stacking, set it's colour and rotate it over the appropriate pile
		stackCoal(getIndexOfStackerReclaimer(stackerReclaimers, actorPointer));
		actorPointer->setRotation(90.0f);
		break;
	case StackerReclaimerStateType::WorkingReclaim: 
		// If the SR is Reclaiming, set it's colour and rotate it over the appropriate pile
		reclaimCoal(getIndexOfStackerReclaimer(stackerReclaimers, actorPointer),0);
		actorPointer->setRotation(-90.0f);
		break;
	default:
		// TODO put both these functions somewhere more sensible where they won't get called every tick.
		stopStackingCoal(getIndexOfStackerReclaimer(stackerReclaimers, actorPointer));
		stopReclaimingCoal(getIndexOfStackerReclaimer(stackerReclaimers, actorPointer),0);
		break;
	}

	//UE_LOG(LogTemp, Warning, TEXT("timeA: %f, timeb: %f positiona: %f, positionb: %f, positionInterpolated: %f Position scale: %f"), float(previousState.time), float(nextState.time), float(previousState.position), float(nextState.position), float(positionInterpolated), float(positionScale));
}

 // HELPER FUNCTION FOR  S-R animateEntity
int ALevelController::getIndexOfStackerReclaimer(TArray<AStackerReclaimer*> array, AStackerReclaimer* actor) {

	for (int i = 0; i < array.Num(); i++) {
		if (array[i] == actor) {
			return i;
		}
	}
	return 0;
}


void ALevelController::animateEntity(AShip* actorPointer, const VesselState& previousState, const VesselState& nextState, float interpolationScale) {

	Vessel::Id targetId = previousState.id;

	if (previousState.type != nextState.type) {
		switch (previousState.type)
		{
		case VesselStateType::Berthed:
			actorPointer->berthed();
			break;
		case VesselStateType::Idle:
		case VesselStateType::Invalid:
			actorPointer->atSea();
			break;
		default:

			break;
		}
	}

}

/*
// TODO move this somewhere else in file
*/
void ALevelController::setStockPileLocation(ACoalStack* actorPointer, const Stockpile::Id& id, std::string padId, double position) {

	if (id.terminal == TerminalId::NCT) {
		//UE_LOG(LogTemp, Warning, TEXT("%f"), float(position));
		int padIdentifier = -1;
		if (padId == "Pad A") {
			padIdentifier = 0;
		}
		else if (padId == "Pad BC") {
			padIdentifier = 1;
		}
		else if (padId == "Pad DE") {
			padIdentifier = 2;
		}
		else if (padId == "Pad FG") {
			padIdentifier = 3;
		}
		else if (padId == "Pad H") {
			padIdentifier = 4;
		}

		if (padIdentifier != -1) { // Now that we have determined  which pad we are using, determine the position along the pad
				
			actorPointer->setPosition(position,
				getPadLength(TerminalId::NCT, padIdentifier),
				NCT_pads_start[padIdentifier]->GetActorLocation(),
				NCT_pads_end[padIdentifier]->GetActorLocation());
			actorPointer->setWidth(NCT_pads_start[padIdentifier]->GetActorScale3D().X); // Also set the width
		}
	}
}


void ALevelController::animateEntity(ACoalStack* actorPointer, const StockpileState& previousState, const StockpileState& nextState, float interpolationScale) {
	//UE_LOG(LogTemp, Warning, TEXT("Coal animate"));

	//FString pad = UTF8_TO_TCHAR(previousState.padID.c_str());
	//UE_LOG(LogTemp, Warning, TEXT("Length: %f"), float(nextState.length));

	// If the Stockpile is currently visible, set it's position in the world
	//if (previousState.position != nextState.position) {
		setStockPileLocation(actorPointer, nextState.id, nextState.padID, nextState.position);
	//}
	// Then set it's quantity
	//if (previousState.length != nextState.length) {
		actorPointer->setQuantity(float(nextState.length));
	//}

	Stockpile::Id targetId = nextState.id;

	switch (nextState.type)
	{
	case StockpileStateType::Created:
		break;
	case StockpileStateType::Reclaiming:
		actorPointer->setQuantity(float(nextState.length));
		break;
	case StockpileStateType::Stacking:
		actorPointer->setQuantity(float(nextState.length));
		break;
	case StockpileStateType::Built:
		break;
	default:

		break;
	}
}

void ALevelController::animateEntity(AShipLoader* actorPointer, const ShiploaderState& previousState, const ShiploaderState& nextState, float interpolationScale) {
	
	Shiploader::Id targetId = previousState.id;
	float minPosition = 0;
	//TODO, assign the correct track length, not just the 0'th one
	float maxPosition = (float)getShipLoaderTrackLength(targetId.terminal);
	//calculate the absolute position of the machine (along it's rail) by interpolating the previous and next positions
	//this idea came from vector mathmemathics, with 1d vectors (efficively scalars) is this case; the formula is: previous+(next - previous)*scale;
	float positionInterpolated = previousState.position + (nextState.position - previousState.position)*interpolationScale;
	//convert the absolute position to a scale between 0.0 and 1.0 which can then be used with the vectors placed manually in the editor.
	float positionScale = (positionInterpolated - minPosition) / (maxPosition - minPosition);
	//update the actor position
	actorPointer->setPosition(positionScale);

}




