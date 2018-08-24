// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelController.h"

#include "scheduling/data/env_config.h"

// Sets default values
ALevelController::ALevelController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelController::BeginPlay()
{
	Super::BeginPlay();

	bool success = deserialize(BINARY_PATH, states);
	for (auto eachObj : std::get<std::map<std::string, std::vector<StackerState>>>(states)) {
		FString fstr = UTF8_TO_TCHAR(eachObj.first.c_str());
		UE_LOG(LogTemp, Warning, TEXT("Stacker name: %s"), *fstr);
		for (auto eachState : eachObj.second) {
			fstr = UTF8_TO_TCHAR(std::to_string(eachState.position).c_str());
			UE_LOG(LogTemp, Warning, TEXT("Stacker Position: %s"), *fstr);
		}
	}
}

// Called every frame
void ALevelController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

