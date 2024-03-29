// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoalStack.h"
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

	void setPosition(float position);
	void setBaseRotation(float degrees);
	void resetRotation();

	UFUNCTION(BlueprintImplementableEvent, Category = "ConveyorBelt")
		void setRotation(float rotation);



	void setMaterial(int choice);

	UFUNCTION(BlueprintImplementableEvent, Category = "ConveyorBelt")
		void ResetMaterial();

	UFUNCTION(BlueprintImplementableEvent, Category = "ConveyorBelt")
		void StackMaterial();

	UFUNCTION(BlueprintImplementableEvent, Category = "ConveyorBelt")
		void ReclaimMaterial();
	
	void rotateMastToCoalStack(ACoalStack* coalStack);

	FVector trackNodeA;
	FVector trackNodeB;
	int trackId;
	FString id;
	
};
