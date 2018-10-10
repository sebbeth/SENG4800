// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShipLoader.generated.h"

UCLASS()
class HVCCC2_API AShipLoader : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShipLoader();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void setPosition(float position);

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
