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
		actor->id = id;
		conveyorBelts.Add(actor);
		return actor;
	}
	return NULL;
}

ATrain * ALevelController::spawnATrain(FString id, FVector position, FRotator rotation,TSubclassOf<class ATrain> blueprint) 
// need position and rotation for spawning on train tracks (splines) or weird positions in respect of rotation could occour in the trains location on the spline
{
	UWorld* world = GetWorld();
	if (world) {
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		ATrain *actor = world->SpawnActor<ATrain>(blueprint, position, rotation, spawnParams);
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

	//UE_LOG(LogTemp, Warning, TEXT("animateEntity AStackerReclaimer"));
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
	//hard coded for 1 xml file, cannot determine amount of trains needed without manually reading the xml file, need a train created event from xml to be tracked .......
	//current file has 58 trains in it, another could have more or less, our tracks only use 6 trains from this list "train5", "train16", "train9", "train19","train20" 
	//however upon investigating the file and name structure its assumed it will be fetching the cycleId for "id" ( "70","72","71","73","74","91")
	//Issues cycleId =70 and trainId = train5 is used for all events, differences in events is another data(time, speed etc) but only the trackId is the most important
	//as not all tracks exist
	/*cant code below need access to trackId from the file, cycleid is useless...
	for (auto eachtrack : (trainTracks))
	{
		if (eachtrack->id == )
		{
			//spawn this train
		}
		
	}
	
	
	OLD CODE TO SPAWN ONLY THE CYCLE ID's OF KNOWN TRAINS CHANGING TO SPAWNING ALL TRAINS IN XML FILE
	std::string nct_IdNames[6] = { "70","72","71","73","74","91" };
	for (int i = 0; i < 6; i++)
	{
		if (id.name == nct_IdNames[i])
		{
			//UE_LOG(LogTemp, Warning, TEXT("found a cycle id %s thenameforbinaryfile: %s "), UTF8_TO_TCHAR(nct_IdNames[i].c_str()), UTF8_TO_TCHAR(id.nameForBinaryFile().c_str()));
			//spawn location is a hidden track
			
		}

	}
	return nullptr;
	*/

	return spawnATrain(UTF8_TO_TCHAR(id.nameForBinaryFile().c_str()), trainTracks[0]->Spline->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World),
		trainTracks[0]->Spline->GetRotationAtSplinePoint(0, ESplineCoordinateSpace::World), train_locomotive_blueprint);
}

void ALevelController::animateEntity(ATrain* actorPointer, const TrainMovementState& previousState, const TrainMovementState& nextState, float interpolationScale)
{
	//UE_LOG(LogTemp, Warning, TEXT("animateEntity TRAINS"));

	//std::string nct_IdNames[6] = { "70","72","71","73","74","91" };

	TrainMovement::Id targetId = previousState.id;
	auto& theMap = std::get<DataMap<TrainMovement>>(data);
	auto targetIterator = theMap.find(targetId);
	if (targetIterator != theMap.end())
	{
		for (auto eachState : (*targetIterator).second.states) //all train movement states
		{
			//UE_LOG(LogTemp, Warning, TEXT("animateEntity TRAINS"));
			if (eachState.type == TrainMovementStateType::Invalid)
			{
				//this is always true its always in an invalid state

				//UE_LOG(LogTemp, Warning, TEXT("invalid states "));// , float(previousState.time), float(nextState.time));
			}

			if (eachState.type == TrainMovementStateType::EnteringTrack) //state seen after train enter track event
			{
				//UE_LOG(LogTemp, Warning, TEXT("EnteringTrack state")); // never reaches here.......................................

				//for each enter trainmovmentstate state we look for the specific track id's of the known tracks (at the moment only have NCT terminal train tracks 
				for (auto eachTrack : (trainTracks))
				{
					//UE_LOG(LogTemp, Warning, TEXT("EnteringTrack traintrackloop"));

					//if we have a matching track id we then check for the appropriate train cycle id
					if (eachState.trackID == std::string(TCHAR_TO_UTF8(*eachTrack->id)))
					{
						UE_LOG(LogTemp, Warning, TEXT("found a track id %s "), UTF8_TO_TCHAR(eachState.trackID.c_str()));
						for (auto eachTrain : (trains))
						{
							UE_LOG(LogTemp, Warning, TEXT("cycle id %s trainId is : %s"), UTF8_TO_TCHAR(eachState.id.name.c_str()), UTF8_TO_TCHAR(*eachTrain->id));
							//check the cycle id matches meaning the train is spawned setup additional information
							if (eachState.id.name == std::string(TCHAR_TO_UTF8(*eachTrain->id))) // match the train id's
							{
								//UE_LOG(LogTemp, Warning, TEXT("FOUND a cycle id %s trainId is : %s"), UTF8_TO_TCHAR(eachState.id.name.c_str()), UTF8_TO_TCHAR(eachState.trainID.c_str()) );
								//check which track its on ?
								eachTrain->trackId.Add(UTF8_TO_TCHAR(eachState.trackID.c_str()));
								eachTrain->startTime.Add(eachState.time); // i believe ill need this to calculate the maths later for the smoothing of animation

								//make sure the start time is correct for this train, 
							}
							else
							{
								// train doesn't exist, so it was never spawned on the hidden track.
							}
						}
					}
					else
					{
						// not an implemented track yet
					}


				}

			}

			else if (eachState.type == TrainMovementStateType::InJunction)//state seen after head leave track event
			{
				for (auto eachTrack : (trainTracks))
				{
					if (eachState.trackID == std::string(TCHAR_TO_UTF8(*eachTrack->id)))
					{
						//make sure the trains exist in the list of trains

						for (auto eachTrain : (trains))
						{
							if (eachState.id.name == std::string(TCHAR_TO_UTF8(*eachTrain->id)))
							{
								//update expected finish time for each train in this track
								eachTrain->endTime.Add(eachState.time);//time of the train leaving the track
							}
							else
							{
								//first occurrence of the trains on implemented tracks this case does not occur HOWEVER, 
								//in the file XML the first event i actually saw was a Train Head Leave Track, NOT a Train Enter Track.
								//This means this case is highly likely to occur in the xml files
								//train never saw an enter track event might just need to spawn at end?? OR assume a travel from start to end on this track?? 

							}
						}

					}

				}
			}//more events carry off this bracket

		}//eachstate loop

		/*
		if (trains[0]->trackId.Num() != 0) // confirms no events are getting fired......
		{

			UE_LOG(LogTemp, Warning, TEXT("train id: %f, track id: %f "), UTF8_TO_TCHAR(*trains[0]->trainId), UTF8_TO_TCHAR(*trains[0]->trackId[0]));

		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("timeA: %f, timeb: %f ") // positiona: %f, positionb: %f, positionInterpolated: %f Position scale: %f")
			//	, float(previousState.time), float(nextState.time)); //, float(previousState.position), float(nextState.position), float(positionInterpolated), float(positionScale));
		}
		//do nice movement stuff here
	}


}

	/*



		if (eachState.trackID == std::string(TCHAR_TO_UTF8(*eachTrack->id)) )
					{
						//if any trackID exists in this list from the entertrack state/event
						//need to check if the train id already exists in our train array
						//if it doesnt we need to spawn a train on this track

						// need to setup the time it is now in this state, to compare later with another time thats for THIS TrainId leaving THIS TrackId


						//UE_LOG(LogTemp, Warning, TEXT("timeA: %s "), eachState.trackID.c_str());

						if (trains.Num() == 0) // should only run into a "true" once as the array's length will no longer be "0"
						{
							//we don't have any trains at all
							//add a new train to the list
							//spawn it somewhere? not sure as i don't want X trains to spawn on top of each other on the same tracks
							spawnATrain(eachState.trainID.c_str(), eachTrack->Spline->GetLocationAtSplinePoint(splineStartPoint, ESplineCoordinateSpace::Local),
								eachTrack->Spline->GetRotationAtSplinePoint(splineStartPoint, ESplineCoordinateSpace::Local), train_locomotive_blueprint);

							trains[0]->trackId.Add(eachState.trackID.c_str());
							trains[0]->startTime.Add(eachState.time);


						}
						else
						{
						}









	train tracks are stored in the array trainTracks
	std::string nct_IdNames[6] = { "70","72","71","73","74",
								  "91" }; //cycle ids, trains are reused in different cycles.....
	//temporary train id holder for testing
	static std::string nct_trainIdNames[6] = { "train5", "train16", "train9", "train19","train20" //trk_NCIG_AR1

											  ,"train16" }; //trk_NCIG_AR2
															//trk_NCIG_AR3 contains no entries
	//id.name

	//get list of all CycleIds in data
	//get list of states
	//	using list states find first TrackEnter States
	//	with TrackEnter State get the trackId, TrainId and time (startTime)
		//Create a TrackEnterList of trackId's trainId's and the time 3 separate arrays same index values
		//for each trackEnter State store the required data

	//Iterate though states for HeadLeaveTrack
		//repeat above this is classed as front of train leaving track (location of the train will spawn on the spline using the front of model as its "center point" )

	//repeat again for TailLeaveTrack as this will more likely affect the carriage(s), (the amount carriages on trains is determined from?)

	//iterate though traintrack array (holds references to all ATrainTrackSpline)
	//to find each track location to be able to setup the startlocation spawning for each train
	//spawn TrackEnter train id at TrackEnter track id at start location of the track(spline)
	//	animation will involve knowing the HeadLeaveTrack id
	// doing maths to interpolate the time differences between the end and start of the track
	//train will despawn at end of HeadLeaveTrack event but will be re-spawned at the next TrackEnter event


	*/
	}
}
