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

using namespace std;

int mock_state;
float mock_level;

// Sets default values
ALevelController::ALevelController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	xMin = std::numeric_limits<double>::infinity();
	xMax = -std::numeric_limits<double>::infinity();
	simTime = 0;
	speed = 1;
}

// Called when the game starts or when spawned
void ALevelController::BeginPlay()
{
	Super::BeginPlay();

	//Data stuff
	bool success = deserialize(BINARY_PATH, states);

	//NOTE: this is a temporary hack for a demo; removes two stackerreclaimers we don't want in the demo so srs 3.56-3.59 show in the demo
	std::get<std::map<std::string, std::vector<StackerState>>>(states).erase("3.21");
	std::get<std::map<std::string, std::vector<StackerState>>>(states).erase("3.22");

	for (auto eachEntity : std::get<std::map<std::string, std::vector<StackerState>>>(states)) {
		FString fstr = UTF8_TO_TCHAR(eachEntity.first.c_str());
		UE_LOG(LogTemp, Warning, TEXT("Stacker name: %s"), *fstr);
		for (auto eachState : eachEntity.second) {
			/*UE_LOG(LogTemp, Warning, TEXT("index: %d, Time: %f; Stacker Position: %f"), i++, eachState.time, eachState.position);*/
			if (eachState.position < xMin) {
				xMin = eachState.position;
			}
			if (eachState.position > xMax) {
				xMax = eachState.position;
			}
		}
		windows.emplace_back(0, std::min(std::size_t(1), eachEntity.second.size()));
	}

	if (windows.size() >= 1) {
		spawnAStackerReclaimer("SR_0", NCT_SR_rails_start[0]->GetActorLocation(), NCT_SR_rails_end[0]->GetActorLocation(), largeSR_blueprint);
	}
	if (windows.size() >= 2) {
		spawnAStackerReclaimer("SR_1", NCT_SR_rails_start[1]->GetActorLocation(), NCT_SR_rails_end[1]->GetActorLocation(), largeSR_blueprint);
	}
	if (windows.size() >= 3) {
		spawnAStackerReclaimer("SR_2", NCT_SR_rails_start[2]->GetActorLocation(), NCT_SR_rails_end[2]->GetActorLocation(), largeSR_blueprint);
	}
	if (windows.size() >= 4) {
		spawnAStackerReclaimer("SR_3", NCT_SR_rails_start[3]->GetActorLocation(), NCT_SR_rails_end[3]->GetActorLocation(), largeSR_blueprint);
	}

	/* Train test */
	spawnATrain("t_0", NCT_pads[1]->GetActorLocation(), train_locomotive_blueprint);


	/*
	spawnAConveyorBelt(conv1_position->GetActorLocation(), conv1_position->GetActorRotation(), conveyor_belt_blueprint);
	conveyorBelts[0]->setMaterial(0);

	spawnAConveyorBelt(conv2_position->GetActorLocation(), conv2_position->GetActorRotation(), conveyor_belt_blueprint);
	conveyorBelts[1]->setMaterial(2);

	//stackerReclaimers[0]->setMaterial(0);
	//stackerReclaimers[1]->setMaterial(2);
	*/




	//testTime = 0;
	//mock_state = 1;
	//mock_level = 0.2;
	// Spawn in reclaimers
	//TODO: SUGGEST TO DO THE APPLICATION OF THESE IN THE BLUEPRINT FLOW GRAPHS INSTEAD OF IN THE DETAILS VIEW FOR CLARITY?
	
	
	////Spawn in ship loaders
	//spawnAShipLoader(FString id, FVector railStart, FVector railEnd, TSubclassOf<class AShipLoader> blueprint)
	spawnAShipLoader("NCT_ShipLoader_01", NCT_loader_rails_start[0]->GetActorLocation(), NCT_loader_rails_end[0]->GetActorLocation(), ship_loader_blueprint);
	spawnAShipLoader("NCT_ShipLoader_02", NCT_loader_rails_start[1]->GetActorLocation(), NCT_loader_rails_end[1]->GetActorLocation(), ship_loader_blueprint);

	//spawnAShipLoader(loader1_rail_start->GetActorLocation(), loader1_rail_end->GetActorLocation(), ship_loader_blueprint);
	//spawnAShipLoader(loader2_rail_start->GetActorLocation(), loader2_rail_end->GetActorLocation(), ship_loader_blueprint);
    //spawnAShipLoader(loader3_rail_start->GetActorLocation(), loader3_rail_end->GetActorLocation(), ship_loader_blueprint);
	//

	//spawnAShip(FString id, FVector position, FRotator rotator, TSubclassOf<class AShip> blueprint)
	spawnAShip("NCT_Ship_01", NCT_berths[0]->GetActorLocation(), NCT_berths[0]->GetActorRotation(), ship_blueprint);
	spawnAShip("NCT_Ship_02", NCT_berths[1]->GetActorLocation(), NCT_berths[1]->GetActorRotation(), ship_blueprint);

	//// Spawn coal stacks
	spawnACoalStack("NCT_CS_1", NCT_pads[0]->GetActorLocation(), NCT_pads[0]->GetActorRotation(), coal_stack_blueprint);
	spawnACoalStack("NCT_CS_2", NCT_pads[1]->GetActorLocation(), NCT_pads[1]->GetActorRotation(), coal_stack_blueprint);
	spawnACoalStack("NCT_CS_3", NCT_pads[2]->GetActorLocation(), NCT_pads[2]->GetActorRotation(), coal_stack_blueprint);
	//spawnACoalStack(padK1_position->GetActorLocation(), padK1_position->GetActorRotation(), coal_stack_blueprint);
	//spawnACoalStack(padK2_position->GetActorLocation(), padK2_position->GetActorRotation(), coal_stack_blueprint);

	//UE_LOG(LogTemp, Warning, TEXT("stackCount: %d"), coalStacks.size());
	//UE_LOG(LogTemp, Warning, TEXT("stack1: %d, stack2: %d, stack3: %d"), coalStacks.at(0), coalStacks.at(1), coalStacks.at(2));
	coalStacks[0]->setQuantity(0.8);
	coalStacks[1]->setQuantity(0.2);
	coalStacks[2]->setQuantity(0.5);
}



void ALevelController::updateSim() {
	auto watchIt = windows.begin();
	auto entIt = std::get<std::map<std::string, std::vector<StackerState>>>(states).begin();
	auto actorIt = stackerReclaimers.CreateConstIterator();
	for (; watchIt != windows.end(); (++watchIt, ++entIt)) {
		auto eachWindow = (*watchIt);
		auto eachEntity = (*entIt);
		while (eachEntity.second[eachWindow.second].time < simTime && eachWindow.second < eachEntity.second.size() - 1) {
			if (eachWindow.first != eachWindow.second) {
				++eachWindow.first;
			}
			++eachWindow.second;
		}
		if (eachEntity.second[eachWindow.second].time < simTime) {
			eachWindow.first = eachWindow.second;
		}
	}
}

void ALevelController::resetSim() {
	for (auto watchIt : windows) {
		watchIt.first = 0;
		watchIt.second = 0;
	}
}
float ALevelController::getSimTime() {
	return simTime;
}

void ALevelController::setSimTime(float absoluteTime) {
	simTime = absoluteTime;
	resetSim();
	updateSim();
}

void ALevelController::moveSimTime(float deltaTime) {
	simTime += deltaTime;
	updateSim();
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

// Called every frame
void ALevelController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// DATA STUFF
	if (isPlaying) {
		moveSimTime(DeltaTime * speed);
		auto watchIt = windows.begin();
		auto entIt = std::get<std::map<std::string, std::vector<StackerState>>>(states).begin();
		auto actorIt = stackerReclaimers.CreateConstIterator();
		for (; watchIt != windows.end() && actorIt; (++watchIt, ++entIt, ++actorIt)) {
			auto eachWindow = (*watchIt);
			auto eachEntity = (*entIt);
			auto eachActor = (*actorIt);
			int indexA = eachWindow.first;
			int indexB = eachWindow.second;


			double timeA = eachEntity.second[indexA].time;
			double timeB = eachEntity.second[indexB].time;

			//the length of time available between the states
			double aToBTimeDist = timeB - timeA;

			//we have to limit the target time in case the worldTime is beyond the current frame
			double targetTime = std::max(timeA, std::min(timeB, simTime));

			//determine the scale as a 
			double scale = aToBTimeDist > 0 ? (targetTime - timeA) / aToBTimeDist : 0;


			double positionA = eachEntity.second[indexA].position;
			double positionB = eachEntity.second[indexB].position;

			double positionInterpolated = positionA + (positionB - positionA)*(scale);

			double positionDelta = (positionInterpolated - xMin) / (xMax - xMin);

			UE_LOG(LogTemp, Warning, TEXT("Name: %s, Time: %f; state a: %d, state b: %d, typea: %d, typeb: %d"), UTF8_TO_TCHAR(eachEntity.first.c_str()), float(simTime), indexA, indexB, (int)eachEntity.second[indexA].type, (int)eachEntity.second[indexB].type);
			UE_LOG(LogTemp, Warning, TEXT("scale: %f, timeA: %f, timeb: %f positiona: %f, positionb: %f, positionInterpolated: %f Position delta: %f"), float(scale), float(timeA), float(timeB), float(positionA), float(positionB), float(positionInterpolated), float(positionDelta));

			// TEST INPUT
			eachActor->setPosition(positionDelta);
		}
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
		actor->id = "SR0";
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

ATrain * ALevelController::spawnATrain(FString id, FVector position, TSubclassOf<class ATrain> blueprint) {
	UWorld* world = GetWorld();
	if (world) {
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		ATrain *actor = world->SpawnActor<ATrain>(blueprint, position, FRotator(0,0,0), spawnParams);
		trains.Add(actor);
		return actor;
	}
	return NULL;
}



