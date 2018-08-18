// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelController.h"
#include "StackerReclaimer.h"
#include "ShipLoader.h"
#include "Ship.h"
#include "CoalStack.h"


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
	// Spawn in reclaimers
	stackerReclaimers[0] = spawnAReclaimer(SR0_rail_start->GetActorLocation(), SR0_rail_end->GetActorLocation(), largeSR_blueprint);
	stackerReclaimers[1] = spawnAReclaimer(SR1_rail_start->GetActorLocation(), SR1_rail_end->GetActorLocation(), largeSR_blueprint);
	stackerReclaimers[2] = spawnAReclaimer(SR2_rail_start->GetActorLocation(), SR2_rail_end->GetActorLocation(), largeSR_blueprint);
	stackerReclaimers[3] = spawnAReclaimer(SR3_rail_start->GetActorLocation(), SR3_rail_end->GetActorLocation(), largeSR_blueprint);
	
	//Spawn in ship loaders
	shipLoaders[0] = spawnAShipLoader(loader0_rail_start->GetActorLocation(), loader0_rail_end->GetActorLocation(), ship_loader_blueprint);
	shipLoaders[1] = spawnAShipLoader(loader1_rail_start->GetActorLocation(), loader1_rail_end->GetActorLocation(), ship_loader_blueprint);
	shipLoaders[2] = spawnAShipLoader(loader2_rail_start->GetActorLocation(), loader2_rail_end->GetActorLocation(), ship_loader_blueprint);
	shipLoaders[3] = spawnAShipLoader(loader3_rail_start->GetActorLocation(), loader3_rail_end->GetActorLocation(), ship_loader_blueprint);

	
	ships[0] = spawnAShip(berth0_position->GetActorLocation(), berth0_position->GetActorRotation(), ship_blueprint);

	coalStacks[0] = spawnACoalStack(padK0_position->GetActorLocation(), padK0_position->GetActorRotation(), coal_stack_blueprint);

	Super::BeginPlay();
	
}

// Called every frame
void ALevelController::Tick(float DeltaTime)
{
	// TEST INPUT
	stackerReclaimers[0]->setPosition(0.6);
	stackerReclaimers[1]->setPosition(0.8);
	stackerReclaimers[0]->setRotation(180);

	shipLoaders[0]->setPosition(0.8);
	coalStacks[0]->setQuantity(0.4);
	if (testTime == 600) {
		ships[0]->Destroy();
	}

	testTime++;

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



ACoalStack * ALevelController::spawnACoalStack(FVector position, FRotator rotator, TSubclassOf<class ACoalStack> blueprint) {
	UWorld* world = GetWorld();
	if (world) {
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		ACoalStack *actor = world->SpawnActor<ACoalStack>(blueprint, position, rotator, spawnParams);
		return actor;
	}
	return NULL;
}


