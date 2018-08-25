// Fill out your copyright notice in the Description page of Project Settings.
#include "LevelController.h"
#include "scheduling/data/env_config.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include <algorithm>

AGlowCube * ALevelController::spawnAGlowCube(FVector start, FVector end) {
	UWorld* world = GetWorld();
	if (world) {
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		AGlowCube *actor = world->SpawnActor<AGlowCube>(glowCubeBlueprintToUse, start, FRotator(0.0f, 0.0f, 0.0f), spawnParams);
		UE_LOG(LogTemp, Warning, TEXT("Pointer: %s"), daCube);
		actor->startPoint = start;
		actor->endPoint = end;
		return actor;
	}
	return NULL;
}

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
	daCube = spawnAGlowCube(startPoint, endPoint);
	UE_LOG(LogTemp, Warning, TEXT("Pointer id: %s"), daCube);
	auto firstObj = std::get<std::map<std::string, std::vector<StackerState>>>(states)["3.58"];
	theWatch.first = 0;
	theWatch.second = std::min(std::size_t(1), firstObj.size()-1);
}

void ALevelController::moveTime(double deltaTime) {
	worldTime += deltaTime;
	auto firstObjStates = std::get<std::map<std::string, std::vector<StackerState>>>(states)["3.58"];
	while (firstObjStates[theWatch.second].time < worldTime && theWatch.second < firstObjStates.size()-1) {
		++theWatch.first;
		++theWatch.second;
	}
	if (firstObjStates[theWatch.second].time < worldTime) {
		theWatch.first = theWatch.second;
	}
}

// Called every frame
void ALevelController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	moveTime(DeltaTime * speed);
	auto firstObjStates = std::get<std::map<std::string, std::vector<StackerState>>>(states)["3.58"];

	int indexA = theWatch.first;
	int indexB = theWatch.second;
	/*while (firstObjStates[indexA].type == firstObjStates[indexB].type && firstObjStates[indexA].position == firstObjStates[indexB].position && theWatch.second < firstObjStates.size() - 1) {
		++indexB;
	}*/
	double timeA = firstObjStates[indexA].time;
	double timeB = firstObjStates[indexB].time;
	
	//the length of time available between the states
	double aToBTimeDist = timeB-timeA;

	//we have to limit the target time in case the worldTime is beyond the current frame
	double targetTime = std::max(timeA, std::min(timeB, worldTime));
	
	//determine the scale as a 
	double scale = aToBTimeDist > 0 ? (targetTime - timeA) / aToBTimeDist : 0;
	

	double positionA = firstObjStates[indexA].position;
	double positionB = firstObjStates[indexB].position;

	double positionInterpolated = positionA + (positionB-positionA)*(scale);

	double positionDelta = (positionInterpolated - xMin) / (xMax - xMin);
	
	UE_LOG(LogTemp, Warning, TEXT("Time: %f; state a: %d, state b: %d, typea: %d, typeb: %d"), float(worldTime), indexA, indexB, (int)firstObjStates[indexA].type, (int)firstObjStates[indexB].type);
	UE_LOG(LogTemp, Warning, TEXT("scale: %f, timeA: %f, timeb: %f positiona: %f, positionb: %f, positionInterpolated: %f Position delta: %f"), float(scale), float(timeA), float(timeB), float(positionA), float(positionB), float(positionInterpolated), float(positionDelta));

	daCube->applyState(positionDelta);
}

