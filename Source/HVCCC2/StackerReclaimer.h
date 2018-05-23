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

	float moveToTarget;
	float rotationTarget;
	float rotationOffset;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector currentLocation;
	FVector targetLocation;

	UPROPERTY(EditAnywhere)
	FVector trackNodeA;

	UPROPERTY(EditAnywhere)
	FVector trackNodeB;

	UPROPERTY(EditAnywhere)
	float slewSpeed;

	int state;
	int task; // temp scheduling variable


	UPROPERTY(EditAnywhere)
	float maxSpeed;
	
	
	float speed;
	

	UFUNCTION(BlueprintCallable, Category = "SR")
	void moveTo(float position);

	UFUNCTION(BlueprintCallable, Category = "SR")
	void rotateTo(float degrees);

};
