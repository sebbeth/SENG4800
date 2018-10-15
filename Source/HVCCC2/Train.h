// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Components/SplineComponent.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "Train.generated.h"

UCLASS()
class HVCCC2_API ATrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame

	void setPosition(float position, USplineComponent* trackSpline);

	void spawnCarriages(TSubclassOf<class AActor> blueprint,int count);

	FString id; // trainId
	int carriageCount;
	TArray<AActor*> carriages;
	TSubclassOf<class AActor> train_carriage_full_blueprint;
	FString cycleId;
	TArray<FString> trackId; //id of the track this train is currently on
//time values represent start and end time of the train on the specified track
	TArray<double> startTime;
	TArray<double> endTime;
};
