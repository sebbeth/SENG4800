// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <string>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "data/extraction/Stockpile/Stockpile.h"
#include "CoalStack.generated.h"


UCLASS()
class HVCCC2_API ACoalStack : public AActor
{
	GENERATED_BODY()
	
private:

	float width;
	float length;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	ACoalStack();

	void setQuantity(float length);
	void setWidth(float width);
	void setPosition(float position, float pileLength, float padLength, FVector padStart, FVector padEnd);
	Stockpile::Id getID();

	Stockpile::Id id;

};
