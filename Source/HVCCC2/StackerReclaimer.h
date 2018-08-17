// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StackerReclaimer.generated.h"

UCLASS()
class HVCCC2_API AStackerReclaimer : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AStackerReclaimer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FVector currentLocation;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void test();
	void setPosition(float position);
	void setRotation(float degrees);
	FVector trackNodeA;
	FVector trackNodeB;
	
};
