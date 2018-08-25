// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelController.h"
#include "StackerReclaimer.h"
#include "ShipLoader.h"
#include "Ship.h"
#include "CoalStack.h"
#include "ConveyorBelt.h"
#include <deque>

using namespace std;

deque<ACoalStack*> coalStacks;
deque<AStackerReclaimer*> stackerReclaimers;
deque<AShipLoader*> shipLoaders;
deque<AShip*> ships;
deque<AConveyorBelt*> conveyorBelts;

int mock_state;
float mock_level;

// Sets default values
ALevelController::ALevelController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelController::BeginPlay()
{
	// Level setup procedure

	testTime = 0;
	mock_state = 1;
	mock_level = 0.2;
	// Spawn in reclaimers
	stackerReclaimers.push_back(spawnAReclaimer(SR0_rail_start->GetActorLocation(), SR0_rail_end->GetActorLocation(), largeSR_blueprint));
	stackerReclaimers.push_back(spawnAReclaimer(SR1_rail_start->GetActorLocation(), SR1_rail_end->GetActorLocation(), largeSR_blueprint));
	stackerReclaimers.push_back(spawnAReclaimer(SR2_rail_start->GetActorLocation(), SR2_rail_end->GetActorLocation(), largeSR_blueprint));
	stackerReclaimers.push_back(spawnAReclaimer(SR3_rail_start->GetActorLocation(), SR3_rail_end->GetActorLocation(), largeSR_blueprint));
	
	//Spawn in ship loaders
	shipLoaders.push_back(spawnAShipLoader(loader0_rail_start->GetActorLocation(), loader0_rail_end->GetActorLocation(), ship_loader_blueprint));
	shipLoaders.push_back(spawnAShipLoader(loader1_rail_start->GetActorLocation(), loader1_rail_end->GetActorLocation(), ship_loader_blueprint));
	shipLoaders.push_back(spawnAShipLoader(loader2_rail_start->GetActorLocation(), loader2_rail_end->GetActorLocation(), ship_loader_blueprint));
	shipLoaders.push_back(spawnAShipLoader(loader3_rail_start->GetActorLocation(), loader3_rail_end->GetActorLocation(), ship_loader_blueprint));

	
	ships.push_back(spawnAShip(berth0_position->GetActorLocation(), berth0_position->GetActorRotation(), ship_blueprint));
	ships.push_back(spawnAShip(berth2_position->GetActorLocation(), berth2_position->GetActorRotation(), ship_blueprint));

	// Spawn coal stacks
	spawnACoalStack(padK0_position->GetActorLocation(), padK0_position->GetActorRotation(), coal_stack_blueprint);
	spawnACoalStack(padK1_position->GetActorLocation(), padK1_position->GetActorRotation(), coal_stack_blueprint);
	spawnACoalStack(padK2_position->GetActorLocation(), padK2_position->GetActorRotation(), coal_stack_blueprint);


	coalStacks.at(0)->setQuantity(0.8);
	coalStacks.at(1)->setQuantity(0.2);
	coalStacks.at(2)->setQuantity(0.5);

	

	Super::BeginPlay();
	
}

// Called every frame
void ALevelController::Tick(float DeltaTime)
{
	// TEST INPUT
	stackerReclaimers.at(0)->setPosition(0.15);
	stackerReclaimers.at(1)->setPosition(0.8);
	stackerReclaimers.at(0)->setRotation(120);

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

	Super::Tick(DeltaTime);

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
		coalStacks.push_back(actor); // Add the new actor to the array
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


