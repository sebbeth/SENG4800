// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <string>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoalStack.generated.h"

UCLASS()
class HVCCC2_API ACoalStack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoalStack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void setQuantity(float length);
	void setPosition(float position, float trackLength, FVector trackStart, FVector trackEnd);

	FString id;

};
