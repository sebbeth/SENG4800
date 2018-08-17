// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelController.h"
#include "StackerReclaimer.h"

AStackerReclaimer *next;

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

	// Spawn in reclaimers
	stackerReclaimers[0] = spawnAReclaimer(FVector(-386290.0f, -183720.0f, -2740.0f), FVector(-288790.0f, -118130.0f, -2740.0f), largeSR_blueprint);
	stackerReclaimers[1] = spawnAReclaimer(FVector(-386690.0f, -200210.0f, -2740.0f), FVector(-283360.0f, -130770.0f, -2740.0f), largeSR_blueprint);
	stackerReclaimers[2] = spawnAReclaimer(FVector(-378230.0f, -210880.0f, -2740.0f), FVector(-274470.0f, -141230.0f, -2740.0f), largeSR_blueprint);
	stackerReclaimers[3] = spawnAReclaimer(FVector(-373080.0f, -223370.0f, -2740.0f), FVector(-268440.0f, -153680.0f, -2740.0f), largeSR_blueprint);


	Super::BeginPlay();
	
}

// Called every frame
void ALevelController::Tick(float DeltaTime)
{
	stackerReclaimers[0]->setPosition(50);
	stackerReclaimers[0]->setRotation(180);

	Super::Tick(DeltaTime);

}

AStackerReclaimer* ALevelController::spawnAReclaimer(FVector railStart, FVector railEnd, TSubclassOf<class AStackerReclaimer> blueprint) {
	

	UE_LOG(LogTemp, Warning, TEXT("Spawning..."));
	UWorld* world = GetWorld();
	if (world) {
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;

		FRotator rotator(0.0f, 0.0f, 0.0f);

		AStackerReclaimer *actor = world->SpawnActor<AStackerReclaimer>(blueprint, railStart, rotator, spawnParams);

		actor->trackNodeA = railStart;
		actor->trackNodeB = railEnd;

		return actor;
	}

	return NULL;
}


