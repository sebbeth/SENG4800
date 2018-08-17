// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelController.h"
#include "StackerReclaimer.h"


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
	FVector start(-276230.0f, -126070.0f, -2740.0f);
	FVector end(-276230.0f, -16070.0f, -2740.0f);

	spawnAReclaimer(FVector(-276230.0f, -126070.0f, -2740.0f), FVector(-276230.0f, -16070.0f, -2740.0f), largeSR_blueprint);
	Super::BeginPlay();
	
}

// Called every frame
void ALevelController::Tick(float DeltaTime)
{
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

		actor->test();

		return actor;
	}

	return NULL;
}


