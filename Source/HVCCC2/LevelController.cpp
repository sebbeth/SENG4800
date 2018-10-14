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

//std::string lastActorId;
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
	loadXMLData(UTF8_TO_TCHAR(XML_PATH.c_str()));
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
		for (auto& eachVessel : std::get<DataMap<Vessel>>(data)) {
			eachVessel.second.determineArrivalLocation(data);
		}
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


int ALevelController::getPadLength(TerminalId terminalId, const std::string & padId)
{
	int padIdentifier = -1;
	if (padId == "PadA") {
		padIdentifier = 0;
	}
	else if (padId == "PadBC") {
		padIdentifier = 1;
	}
	else if (padId == "PadDE") {
		padIdentifier = 2;
	}
	else if (padId == "PadFG") {
		padIdentifier = 3;
	}
	else if (padId == "PadH") {
		padIdentifier = 4;
	}
	return getPadLength(terminalId, padIdentifier);
}

/*
	Terminal ID - the ids will link to a terminal (KCT, NCIG, CCT), the Padwill also have an ID value.
*/
int ALevelController::getPadLength(TerminalId terminal, const int& padId) {
	// KCT Terminal Pads.
	
	switch (terminal) {
		case TerminalId::KCT:
			switch(padId) {
				case 0: // Pada
					return 2285;
				case 1: // Padb
					return 2180;
				case 2: //Padc
					return 2155;
				case 3: //Padd
					return 2315;
					
			}
		case TerminalId::NCT:
			switch (padId) {
				case 0: // Pada
					return 1055;
				case 1: // Padbc
					return 1100;
				case 2: //Padde
					return 1113;
				case 3: //Padfg
					return 1160;
				case 4: // PadH
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

//Returns the amount of the stockpile for use in the object selection box
TArray<FString> ALevelController::getStateInfo(ACoalStack* actor) {
	const SimulationData<Stockpile>& simData = std::get<DataMap<Stockpile>>(this->data).at(actor->getID());
	const StockpileState& previous = *simData.stateWindow.first;
	const StockpileState& next = *simData.stateWindow.second;

	const FString id = UTF8_TO_TCHAR(actor->getID().name.c_str());
	const double coverage = (previous.amount/simData.maximumAmount) * 100;
	const double current = previous.amount;
	const double change = next.amount - previous.amount;
	
	TArray<FString> stateInfo;
	
	// If you change the order of the TArray you will need to change the logic in the FlyingGameMode Blueprint
	stateInfo.Add(id);
	stateInfo.Add(FString::SanitizeFloat(current));
	stateInfo.Add(FString::SanitizeFloat(coverage) + "%");
	
	if (change != 0) {
		if (change > 0)
			stateInfo.Add("+" + FString::SanitizeFloat(change));
		else
			stateInfo.Add(FString::SanitizeFloat(change));
	} 
	else
		stateInfo.Add("");
	
	stateInfo.Add(id);

	return stateInfo;
}

ACoalStack * ALevelController::spawnACoalStack(Stockpile::Id id, FVector position, FRotator rotator, float width, TSubclassOf<class ACoalStack> blueprint) {
	UWorld* world = GetWorld();
	if (world) {
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		ACoalStack *actor = world->SpawnActor<ACoalStack>(blueprint, position, rotator, spawnParams);
		// UE_LOG(LogTemp, Warning, TEXT("%s"), *id);
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
				return spawnAStackerReclaimer(UTF8_TO_TCHAR(id.nameForBinaryFile().c_str()),i, NCT_SR_rails_start[i]->GetActorLocation(), NCT_SR_rails_end[i]->GetActorLocation(), largeSR_blueprint);
			}
		}
	}
	return nullptr;
}



AShip* ALevelController::getOrSpawnActor(const Vessel::Id& id) {
	static std::string nct_names[4] = { "SHIP:1", "SHIP:2", "SHIP:3", "SHIP:4" };
	FString ff = UTF8_TO_TCHAR(id.name.c_str());
	//UE_LOG(LogTemp, Warning, TEXT("SHIP:%s"), *ff);
	//if (id.terminal == TerminalId::NCT) {
		//for (int i = 0; i < 4; ++i) {
		//	if (id.name == nct_names[i]) {
				return spawnAShip(UTF8_TO_TCHAR(id.nameForBinaryFile().c_str()), FVector(), FRotator(), ship_blueprint);
		//	}
		//}
	//}
	return nullptr;
}


ACoalStack* ALevelController::getOrSpawnActor(const Stockpile::Id& id) {
	if (id.terminal == TerminalId::NCT) {
		// NOTE actors are being spawned to 0,0,0 rather then being spawned and then made invisible
		return spawnACoalStack(id, FVector(0, 0, 0), NCT_pads_start[0]->GetActorRotation(), 0, coal_stack_blueprint);
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
	float positionInterpolated = previousState.position + (nextState.position - previousState.position)*interpolationScale - 50;
	//convert the absolute position to a scale between 0.0 and 1.0 which can then be used with the vectors placed manually in the editor.
	float positionScale = (positionInterpolated - minPosition) / (maxPosition - minPosition);
	//update the actor position
	actorPointer->setPosition(positionScale);
	//TODO: ADD TURNING CONSIDERATIONS
		
	switch (previousState.type)
	{
	case StackerReclaimerStateType::Moving:
		 // If the SR is moving, set it's arm to forward
		actorPointer->resetRotation(); // The SR needs to point at this coalStack
	
		break;
	case StackerReclaimerStateType::WorkingStack: 

		// If the SR is Stacking, set it's colour and rotate it over the appropriate pile
		stackCoal(getIndexOfStackerReclaimer(stackerReclaimers, actorPointer));
		actorPointer->rotateMastToCoalStack(getCoalStackWithId(previousState.stockpileID)); // The SR needs to point at this coalStack
		break;
	case StackerReclaimerStateType::WorkingReclaim: 

		// If the SR is Reclaiming, set it's colour and rotate it over the appropriate pile
		reclaimCoal(getIndexOfStackerReclaimer(stackerReclaimers, actorPointer),0);
		actorPointer->rotateMastToCoalStack(getCoalStackWithId(previousState.stockpileID));
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

ACoalStack * ALevelController::getCoalStackWithId(Stockpile::Id id)
{
	return std::get<DataMap<Stockpile>>(data).at(id).actorPointer;
}

void ALevelController::animateEntity(const SimulationData<Vessel>& data, float interpolationScale) {
	auto& previousState = *data.stateWindow.first;
	auto& nextState = *data.stateWindow.second;

	
	FVector berthStart;
	FVector berthEnd;
	FVector berthVector;
	double berthLength;
	double positionScale;
	double unrealBerthSize;
	switch (previousState.type) {
	case VesselStateType::Berthed:
		
		switch (data.terminal) {
		case TerminalId::NCT:
			berthStart = NCT_berth_start->GetActorLocation();
			berthEnd = NCT_berth_end->GetActorLocation();//do stuff
			data.actorPointer->berthed();
			berthVector = berthEnd - berthStart;
			//TODO, assign the correct track length, not just the 0'th one
			berthLength = getShipLoaderTrackLength(data.terminal);
			positionScale = data.berthPosition / berthLength;
			unrealBerthSize = berthVector.Size();
			berthVector.Normalize();
			data.actorPointer->SetActorRotation(NCT_berth_start->GetActorRotation());
			data.actorPointer->SetActorLocation(berthStart + berthVector * unrealBerthSize * positionScale);
			break;
		default:
			return; //don't bother showing
		}
		
		
		break;
	case VesselStateType::Idle:
	case VesselStateType::Invalid:
		data.actorPointer->atSea();
		break;
	default:

		break;
	}

}

/*
// TODO move this somewhere else in file
*/
//void ALevelController::setStockPileLocation(ACoalStack* actorPointer, const Stockpile::Id& id, std::string padId, double position) {
//
//	if (id.terminal == TerminalId::NCT) {
//		//UE_LOG(LogTemp, Warning, TEXT("%f"), float(position));
//		int padIdentifier = -1;
//		if (padId == "PadA") {
//			padIdentifier = 0;
//		}
//		else if (padId == "PadBC") {
//			padIdentifier = 1;
//		}
//		else if (padId == "PadDE") {
//			padIdentifier = 2;
//		}
//		else if (padId == "PadFG") {
//			padIdentifier = 3;
//		}
//		else if (padId == "PadH") {
//			padIdentifier = 4;
//		}
//
//		if (padIdentifier != -1) { // Now that we have determined  which Padwe are using, determine the position along the pad
//				
//			actorPointer->setGeometry(position,
//				getPadLength(TerminalId::NCT, padIdentifier),
//				NCT_pads_start[padIdentifier]->GetActorLocation(),
//				NCT_pads_end[padIdentifier]->GetActorLocation());
//			actorPointer->setWidth(NCT_pads_start[padIdentifier]->GetActorScale3D().X); // Also set the width
//		}
//	}
//}


void ALevelController::animateEntity(const SimulationData<Stockpile>& data, float interpolationScale) {
	//Commented out code provides hinting on types, and an example of how to get the variables used in the simpler animateEntity
	//using State = typename Entity::State;
	ACoalStack* actorPointer = data.actorPointer;
	const StockpileState& previousState = (*data.stateWindow.first);
	const StockpileState& nextState = (*data.stateWindow.second);

	Stockpile::Id targetId = nextState.id;
	
	//get Padinfo
	int padIdentifier = -1;
	if (targetId.terminal == TerminalId::NCT) {
		//UE_LOG(LogTemp, Warning, TEXT("%f"), float(position));
		if (previousState.padID == "PadA" || previousState.padID == "Pad A") {
			padIdentifier = 0;
		}
		else if (previousState.padID == "PadBC" || previousState.padID == "Pad BC") {
			padIdentifier = 1;
		}
		else if (previousState.padID == "PadDE" || previousState.padID == "Pad DE") {
			padIdentifier = 2;
		}
		else if (previousState.padID == "PadFG" || previousState.padID == "Pad FG") {
			padIdentifier = 3;
		}
		else if (previousState.padID == "PadH" || previousState.padID == "Pad H") {
			padIdentifier = 4;
		}
	}
	

	if (padIdentifier != -1) { // Now that we have determined  which Pad we are using, determine the position along the pad
		//UE_LOG(LogTemp, Warning, TEXT("PAD IDENT IS %d"), padIdentifier);
		auto padStart = NCT_pads_start[padIdentifier]->GetActorLocation();
		auto padEnd = NCT_pads_end[padIdentifier]->GetActorLocation();

		int padLength = getPadLength(TerminalId::NCT, padIdentifier);
		double instantaneousAmount = previousState.amount + (nextState.amount - previousState.amount)*interpolationScale;
		double pileProportion = instantaneousAmount / data.maximumAmount;

		double padLengthScale = FVector::Dist(padEnd, padStart)/padLength;

		double pileScale = (pileProportion*previousState.length*padLengthScale);
		actorPointer->setGeometry(previousState.position, pileProportion, previousState.length,
			padLength,
			NCT_pads_start[padIdentifier]->GetActorLocation(),
			NCT_pads_end[padIdentifier]->GetActorLocation());
		actorPointer->setWidth(NCT_pads_start[padIdentifier]->GetActorScale3D().X); // Also set the width

		//also set the rotation
		actorPointer->SetActorRotation(NCT_pads_start[padIdentifier]->GetActorRotation());

		//actorPointer->setQuantity(float(pileScale));
		//switch (nextState.type)
		//{
		//case StockpileStateType::Created:
		//	break;
		//case StockpileStateType::Reclaiming:
		//	actorPointer->setQuantity(float(nextState.length));
		//	break;
		//case StockpileStateType::Stacking:
		//	actorPointer->setQuantity(float(nextState.length));
		//	break;
		//case StockpileStateType::Built:
		//	break;
		//default:

		//	break;
		//}
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
	switch (previousState.type)
	{
	case ShiploaderStateType::Working:
		actorPointer->ReclaimMaterial();
		break;
	default:
		actorPointer->ResetMaterial();
		break;
	}
}


ATrain* ALevelController::getOrSpawnActor(const TrainMovement::Id& id)
{
	//stub
	//UE_LOG(LogTemp, Warning, TEXT("Added a Train found a train id %s "), UTF8_TO_TCHAR(id.nameForBinaryFile().c_str()));
	return spawnATrain(UTF8_TO_TCHAR(id.nameForBinaryFile().c_str()), trainTracks[0]->Spline->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World),
		trainTracks[0]->Spline->GetRotationAtSplinePoint(0, ESplineCoordinateSpace::World), train_locomotive_blueprint);
	//return nullptr;
}


void ALevelController::animateEntity(const SimulationData<TrainMovement>& data, float interpolationScale) {
	//in theory, this logic searches for the state pairs that get the moment of entry for the current track and the next track, ignoring irrelevant states like in junction; additional cases will be needed to handle maintenance etc, but otherwise this should work I think?
	//in future, the xml data should possibly be modified to only provide entering track states maybe for movement (plus maintenance or whatever)?
	auto enterIterator = data.stateWindow.first;
	auto exitIterator = data.stateWindow.second;
	std::string targetTrackId;
	if (enterIterator->type == TrainMovementStateType::EnteringTrack) { 
		targetTrackId = (*enterIterator).trackID;
		exitIterator = enterIterator;
	} else if(enterIterator->type == TrainMovementStateType::LeavingTrack){
		targetTrackId = (*exitIterator).trackID;
		enterIterator = exitIterator;
	}
	ATrainTrackSpline* targetTrackPtr = nullptr;
	//first try and find the track we want;
	// next state the train is leaving this track iterate for the track in previous state as we haven't left the track until interpolationScale == 1.0
	for (auto& eachTrackPtr : trainTracks) {
		if (targetTrackId == std::string(TCHAR_TO_UTF8(*eachTrackPtr->id))) {
			targetTrackPtr = eachTrackPtr;
			break;
		}
	}

	bool shouldShow = targetTrackPtr != nullptr;

	// only bother animating fully if we recognise the track
	if (shouldShow) {
		while (enterIterator != data.states.begin() && (*(enterIterator-1)).trackID == targetTrackId) {
			--enterIterator;
		}
		if ((*enterIterator).trackID != (*data.stateWindow.first).trackID) {
			//panic this was unexpected
			shouldShow = false;
		}
		while (exitIterator+1 != data.states.end() && (*(exitIterator+1)).trackID == targetTrackId) {
			++exitIterator;
		}
		if ((*exitIterator).trackID != (*data.stateWindow.first).trackID) {
			//panic this was unexpected
			shouldShow = false;
		}
	}

	auto actorPointer = data.actorPointer;
	if (shouldShow) {
		//override interpolation scale with a value that actually indicates how far along the track we are
		float targetTime = std::max(enterIterator->time, std::min(exitIterator->time, this->simTime));

		float splineScale;
		if (enterIterator == exitIterator) {
			//if the states are the same, all values between 0 and 1 for the scale would be effectively the same, but the formula would be unable to divide by 0
			splineScale = 0;
		} else {
			//determine the interpolation scale using the the formula |current - previous|/|next - previous|
			splineScale = (targetTime - enterIterator->time) / (exitIterator->time - enterIterator->time);
		}
		//do whatever with an interpolation scale that estimates how far along the track we are
		actorPointer->SetActorHiddenInGame(false);
		//actorPointer->SetActorEnableCollision(true);

		//double sinedScale = std::atan(splineScale);
		
		double distance = targetTrackPtr->Spline->GetSplineLength() * splineScale;
		auto makeTransform = FTransform(targetTrackPtr->Spline->GetRotationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World),
			targetTrackPtr->Spline->GetLocationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World),
			FVector(5.0f, 5.0f, 5.0f));

		actorPointer->SetActorTransform(makeTransform);
	} else {
		//do whatever to hide the train

		actorPointer->SetActorHiddenInGame(true);
		//actorPointer->SetActorEnableCollision(false);

		//auto makeTransform = FTransform(trainTracks[0]->Spline->GetRotationAtSplinePoint(0, ESplineCoordinateSpace::World),
		//	trainTracks[0]->Spline->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World),
		//	FVector(5.0f, 5.0f, 5.0f));

		//actorPointer->SetActorTransform(makeTransform);
	}
}