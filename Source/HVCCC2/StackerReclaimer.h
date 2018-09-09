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

	void setPosition(float position);
	void setBaseRotation(float degrees);

	//UFUNCTION(BlueprintImplementableEvent, Category = "ConveyorBelt")
	void setRotation();

	void setMaterial(int choice);

	UFUNCTION(BlueprintImplementableEvent, Category = "ConveyorBelt")
		void ResetMaterial();

	UFUNCTION(BlueprintImplementableEvent, Category = "ConveyorBelt")
		void StackMaterial();

	UFUNCTION(BlueprintImplementableEvent, Category = "ConveyorBelt")
		void ReclaimMaterial();


	FVector trackNodeA;
	FVector trackNodeB;
	FString id;
	
};
