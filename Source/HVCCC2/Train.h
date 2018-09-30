// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
	virtual void Tick(float DeltaTime) override;

	void setPosition(float position);

	FString id;
	FString cycleId; //maybe, maybe not somthing else not sure what to do with that xml data
	TArray<FString> trackId; //id of the track this train is currently on
	//time values represent start and end time of the train on the specified track
	TArray<double> startTime;
	TArray<double> endTime;

	//might need to be arrays???
	
};
