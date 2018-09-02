// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelController.h"
#include "StackerReclaimer.h"
#include "ShipLoader.h"
#include "Ship.h"
#include "CoalStack.h"
#include "ConveyorBelt.h"
#include <deque>

#include "scheduling/data/serialization.h"

#include "scheduling/data/env_config.h"
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
	worldTime = 0;
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
		stackerReclaimers.Add(spawnAReclaimer(SR0_rail_start->GetActorLocation(), SR0_rail_end->GetActorLocation(), largeSR_blueprint));
	}
	if (windows.size() >= 2) {
		stackerReclaimers.Add(spawnAReclaimer(SR1_rail_start->GetActorLocation(), SR1_rail_end->GetActorLocation(), largeSR_blueprint));
	}
	if (windows.size() >= 3) {
		stackerReclaimers.Add(spawnAReclaimer(SR2_rail_start->GetActorLocation(), SR2_rail_end->GetActorLocation(), largeSR_blueprint));
	}
	if (windows.size() >= 4) {
		stackerReclaimers.Add(spawnAReclaimer(SR3_rail_start->GetActorLocation(), SR3_rail_end->GetActorLocation(), largeSR_blueprint));
	}

	// Level setup procedure
	
	//currently unused codification of stacker positions
	/*stackerReclaimers.Add(spawnAReclaimer(FVector(-388140.0, -185080.0, -650.0), FVector(-288140.0, -117870.0, -650.0), largeSR_blueprint));
	stackerReclaimers.Add(spawnAReclaimer(FVector(-384350.0, -198780.0, -650.0), FVector(-281070.0, -129330.0, -650.0), largeSR_blueprint));
	stackerReclaimers.Add(spawnAReclaimer(FVector(-380530.0, -212410.0, -650.0), FVector(-275020.0, -141400.0, -650.0), largeSR_blueprint));
	stackerReclaimers.Add(spawnAReclaimer(FVector(-375470.0, -225210.0, -650.0), FVector(-268670.0, -153550.0, -650.0), largeSR_blueprint));*/


	//testTime = 0;
	//mock_state = 1;
	//mock_level = 0.2;
	// Spawn in reclaimers
	//TODO: SUGGEST TO DO THE APPLICATION OF THESE IN THE BLUEPRINT FLOW GRAPHS INSTEAD OF IN THE DETAILS VIEW FOR CLARITY?
	
	
	////Spawn in ship loaders
	//shipLoaders.Add(spawnAShipLoader(loader0_rail_start->GetActorLocation(), loader0_rail_end->GetActorLocation(), ship_loader_blueprint));
	//shipLoaders.Add(spawnAShipLoader(loader1_rail_start->GetActorLocation(), loader1_rail_end->GetActorLocation(), ship_loader_blueprint));
	//shipLoaders.Add(spawnAShipLoader(loader2_rail_start->GetActorLocation(), loader2_rail_end->GetActorLocation(), ship_loader_blueprint));
	//shipLoaders.Add(spawnAShipLoader(loader3_rail_start->GetActorLocation(), loader3_rail_end->GetActorLocation(), ship_loader_blueprint));

	//
	//ships.Add(spawnAShip(berth0_position->GetActorLocation(), berth0_position->GetActorRotation(), ship_blueprint));
	//ships.Add(spawnAShip(berth2_position->GetActorLocation(), berth2_position->GetActorRotation(), ship_blueprint));

	//// Spawn coal stacks
	//spawnACoalStack(padK0_position->GetActorLocation(), padK0_position->GetActorRotation(), coal_stack_blueprint);
	//spawnACoalStack(padK1_position->GetActorLocation(), padK1_position->GetActorRotation(), coal_stack_blueprint);
	//spawnACoalStack(padK2_position->GetActorLocation(), padK2_position->GetActorRotation(), coal_stack_blueprint);

	//UE_LOG(LogTemp, Warning, TEXT("stackCount: %d"), coalStacks.size());
	//UE_LOG(LogTemp, Warning, TEXT("stack1: %d, stack2: %d, stack3: %d"), coalStacks.at(0), coalStacks.at(1), coalStacks.at(2));
	//coalStacks.at(0)->setQuantity(0.8);
	//coalStacks.at(1)->setQuantity(0.2);
	//coalStacks.at(2)->setQuantity(0.5);
}


void ALevelController::moveTime(double deltaTime) {
	worldTime += deltaTime;
	auto watchIt = windows.begin();
	auto entIt = std::get<std::map<std::string, std::vector<StackerState>>>(states).begin();
	auto actorIt = stackerReclaimers.CreateConstIterator();
	for (; watchIt != windows.end(); (++watchIt, ++entIt)) {
		auto eachWindow = (*watchIt);
		auto eachEntity = (*entIt);
		while (eachEntity.second[eachWindow.second].time < worldTime && eachWindow.second < eachEntity.second.size() - 1) {
			if (eachWindow.first != eachWindow.second) {
				++eachWindow.first;
			}
			++eachWindow.second;
		}
		if (eachEntity.second[eachWindow.second].time < worldTime) {
			eachWindow.first = eachWindow.second;
		}
	}
}

// Called every frame
void ALevelController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// DATA STUFF

	moveTime(DeltaTime * speed);
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
		double targetTime = std::max(timeA, std::min(timeB, worldTime));

		//determine the scale as a 
		double scale = aToBTimeDist > 0 ? (targetTime - timeA) / aToBTimeDist : 0;


		double positionA = eachEntity.second[indexA].position;
		double positionB = eachEntity.second[indexB].position;

		double positionInterpolated = positionA + (positionB - positionA)*(scale);

		double positionDelta = (positionInterpolated - xMin) / (xMax - xMin);

		UE_LOG(LogTemp, Warning, TEXT("Name: %s, Time: %f; state a: %d, state b: %d, typea: %d, typeb: %d"), UTF8_TO_TCHAR(eachEntity.first.c_str()), float(worldTime), indexA, indexB, (int)eachEntity.second[indexA].type, (int)eachEntity.second[indexB].type);
		UE_LOG(LogTemp, Warning, TEXT("scale: %f, timeA: %f, timeb: %f positiona: %f, positionb: %f, positionInterpolated: %f Position delta: %f"), float(scale), float(timeA), float(timeB), float(positionA), float(positionB), float(positionInterpolated), float(positionDelta));

		// TEST INPUT
		eachActor->setPosition(positionDelta);
	}
}





/*
Spawn functions for actor
*/
AShipLoader* ALevelController::spawnAShipLoader(FVector railStart, FVector railEnd, TSubclassOf<class AShipLoader> blueprint) {

	UWorld* world = GetWorld();
	if (world) {
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		AShipLoader *actor = world->SpawnActor<AShipLoader>(blueprint, railStart, FRotator(0.0f, 0.0f, 0.0f), spawnParams);
		actor->trackNodeA = railStart;
		actor->trackNodeB = railEnd;
		return actor;
	}
	return NULL;
}

AStackerReclaimer* ALevelController::spawnAReclaimer(FVector railStart, FVector railEnd, TSubclassOf<class AStackerReclaimer> blueprint) {
	
	UWorld* world = GetWorld();
	if (world) {
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		AStackerReclaimer *actor = world->SpawnActor<AStackerReclaimer>(blueprint, railStart, FRotator(0.0f, 0.0f, 0.0f), spawnParams);
		actor->trackNodeA = railStart;
		actor->trackNodeB = railEnd;
		actor->id = "SR0";
		return actor;
	}
	return NULL;
}


AShip* ALevelController::spawnAShip(FVector position, FRotator rotator, TSubclassOf<class AShip> blueprint) {
	
	UWorld* world = GetWorld();
	if (world) {
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		AShip *actor = world->SpawnActor<AShip>(blueprint, position, rotator, spawnParams);
		return actor;
	}
	return NULL;
}



void ALevelController::spawnACoalStack(FVector position, FRotator rotator, TSubclassOf<class ACoalStack> blueprint) {
	UWorld* world = GetWorld();
	if (world) {
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		ACoalStack *actor = world->SpawnActor<ACoalStack>(blueprint, position, rotator, spawnParams);
		coalStacks.Add(actor); // Add the new actor to the array
	}
}


AConveyorBelt* ALevelController::spawnAConveyorBelt(FVector position, FRotator rotator, TSubclassOf<class AConveyorBelt> blueprint) {

	UWorld* world = GetWorld();
	if (world) {
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		AConveyorBelt *actor = world->SpawnActor<AConveyorBelt>(blueprint, position, rotator, spawnParams);
		return actor;
	}
	return NULL;


}


