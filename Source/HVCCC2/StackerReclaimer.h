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

private:

	int moveToPosition;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector currentLocation;
	FVector targetLocation;

	FVector trackNodeA;
	FVector trackNodeB;

	int state;
	int task; // temp scheduling variable



	float speed;
	

	UFUNCTION(BlueprintCallable, Category = "SR")
	void moveTo(int position);
};
