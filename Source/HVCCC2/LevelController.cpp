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

	/*static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/Blueprints/BP_StackerReclaimer.BP_StackerReclaimer'"));
	if (ItemBlueprint.Object) {
		largeSR_blueprint = (UClass*)ItemBlueprint.Object->GeneratedClass;
	}*/

	std::string AbsoluteFilePath = std::string(TCHAR_TO_UTF8(*FPaths::GameDir()));
	std::string RelativePath = std::string(TCHAR_TO_UTF8(*FPaths::GameContentDir()));

	std::fstream fileStrm("C:/Users/SENG/Documents/file.txt", std::fstream::out);
	fileStrm << AbsoluteFilePath << std::endl << RelativePath << std::endl;
	fileStrm.flush();
	fileStrm.close();
}

// Called when the game starts or when spawned
void ALevelController::BeginPlay()
{
	Super::BeginPlay();

	// Level setup procedure
	
	//codification of stacker positions
	stackerReclaimers.Add(spawnAReclaimer(FVector(-388140.0, -185080.0, -650.0), FVector(-288140.0, -117870.0, -650.0), largeSR_blueprint));
	stackerReclaimers.Add(spawnAReclaimer(FVector(-384350.0, -198780.0, -650.0), FVector(-281070.0, -129330.0, -650.0), largeSR_blueprint));
	stackerReclaimers.Add(spawnAReclaimer(FVector(-380530.0, -212410.0, -650.0), FVector(-275020.0, -141400.0, -650.0), largeSR_blueprint));
	stackerReclaimers.Add(spawnAReclaimer(FVector(-375470.0, -225210.0, -650.0), FVector(-268670.0, -153550.0, -650.0), largeSR_blueprint));


	//testTime = 0;
	//mock_state = 1;
	//mock_level = 0.2;
	// Spawn in reclaimers
	/*stackerReclaimers.Add(spawnAReclaimer(SR0_rail_start->GetActorLocation(), SR0_rail_end->GetActorLocation(), largeSR_blueprint));
	stackerReclaimers.Add(spawnAReclaimer(SR1_rail_start->GetActorLocation(), SR1_rail_end->GetActorLocation(), largeSR_blueprint));
	stackerReclaimers.Add(spawnAReclaimer(SR2_rail_start->GetActorLocation(), SR2_rail_end->GetActorLocation(), largeSR_blueprint));
	stackerReclaimers.Add(spawnAReclaimer(SR3_rail_start->GetActorLocation(), SR3_rail_end->GetActorLocation(), largeSR_blueprint));*/
	
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




	//DATA STUFF
	

	FVector startPoint(-425, -425, 100);
	FVector endPoint(425, 425, 100);

	bool success = deserialize(BINARY_PATH, states);
	int i = 0;
	for (auto eachObj : std::get<std::map<std::string, std::vector<StackerState>>>(states)) {
		FString fstr = UTF8_TO_TCHAR(eachObj.first.c_str());
		UE_LOG(LogTemp, Warning, TEXT("Stacker name: %s"), *fstr);
		for (auto eachState : eachObj.second) {
			UE_LOG(LogTemp, Warning, TEXT("index: %d, Time: %f; Stacker Position: %f"), i++, eachState.time, eachState.position);
			if (eachState.position < xMin) {
				xMin = eachState.position;
			}
			if (eachState.position > xMax) {
				xMax = eachState.position;
			}
		}
	}
	//daCube = spawnAGlowCube(startPoint, endPoint);
	//UE_LOG(LogTemp, Warning, TEXT("Pointer id: %s"), daCube);
	auto firstObj = std::get<std::map<std::string, std::vector<StackerState>>>(states)["3.58"];
	theWatch.first = 0;
	theWatch.second = std::min(std::size_t(1), firstObj.size() - 1);







	
}

// Called every frame
void ALevelController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// DATA STUFF

	moveTime(DeltaTime * speed);
	auto firstObjStates = std::get<std::map<std::string, std::vector<StackerState>>>(states)["3.58"];

	int indexA = theWatch.first;
	int indexB = theWatch.second;

	
	double timeA = firstObjStates[indexA].time;
	double timeB = firstObjStates[indexB].time;

	//the length of time available between the states
	double aToBTimeDist = timeB - timeA;

	//we have to limit the target time in case the worldTime is beyond the current frame
	double targetTime = std::max(timeA, std::min(timeB, worldTime));

	//determine the scale as a 
	double scale = aToBTimeDist > 0 ? (targetTime - timeA) / aToBTimeDist : 0;


	double positionA = firstObjStates[indexA].position;
	double positionB = firstObjStates[indexB].position;

	double positionInterpolated = positionA + (positionB - positionA)*(scale);

	double positionDelta = (positionInterpolated - xMin) / (xMax - xMin);

	UE_LOG(LogTemp, Warning, TEXT("Time: %f; state a: %d, state b: %d, typea: %d, typeb: %d"), float(worldTime), indexA, indexB, (int)firstObjStates[indexA].type, (int)firstObjStates[indexB].type);
	UE_LOG(LogTemp, Warning, TEXT("scale: %f, timeA: %f, timeb: %f positiona: %f, positionb: %f, positionInterpolated: %f Position delta: %f"), float(scale), float(timeA), float(timeB), float(positionA), float(positionB), float(positionInterpolated), float(positionDelta));
	
	// TEST INPUT
	for (auto each : stackerReclaimers) {
		each->setPosition(positionDelta);
	}
	/*
	shipLoaders.at(0)->setPosition(0.8);
	//coalStacks[0]->setQuantity(0.4);
	if (testTime == 600) {
		ships.at(0)->Destroy();
	}

	testTime++;
	
	if (testTime % 500 == 0) {
		if (mock_state == 1) {
			mock_state = 2;
		} else {
			mock_state = 1;
		}
	}
	
	if (mock_state ==  1) {
		mock_level = mock_level + 0.001f;
		stackerReclaimers.at(3)->setPosition(mock_level);
	
	}

	if (mock_state == 2) {
		mock_level = mock_level - 0.001f;
		stackerReclaimers.at(3)->setPosition(mock_level);

	}
		coalStacks.at(0)->setQuantity(mock_level);
		*/


}



void ALevelController::moveTime(double deltaTime) {
	worldTime += deltaTime;
	auto firstObjStates = std::get<std::map<std::string, std::vector<StackerState>>>(states)["3.58"];
	while (firstObjStates[theWatch.second].time < worldTime && theWatch.second < firstObjStates.size() - 1) {
		++theWatch.first;
		++theWatch.second;
	}
	if (firstObjStates[theWatch.second].time < worldTime) {
		theWatch.first = theWatch.second;
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


