// Fill out your copyright notice in the Description page of Project Settings.

#include "CoalStack.h"

using namespace std;

// Sets default values
ACoalStack::ACoalStack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ACoalStack::BeginPlay()
{
	Super::BeginPlay();
	rawSize = GetComponentsBoundingBox().GetSize() / GetActorScale();
}


void ACoalStack::setGeometry(float position, float proportionFilled, float pileLength, float padLength, FVector padStart, FVector padEnd) {
	if (proportionFilled == 0.0f) {
		SetActorHiddenInGame(true);
	} else {
		FVector padVector = padEnd - padStart;
		FVector directionVector = padVector;
		directionVector.Normalize();

		double padLengthScale = padVector.Size() / padLength; //the ratio between the size of the pad in unreal and the size of the pad in the data's space
		double unrealStartPoint = (position*padLengthScale); // The position along the pad of the start end of the pile in unreal
		double fullSize = pileLength * padLengthScale;
		double currentSize = (proportionFilled*fullSize); //The size of the pile in unreal units
		double unrealCenterPosition = unrealStartPoint + (fullSize /2);
		SetActorLocation(padStart + directionVector * unrealCenterPosition);
		SetActorHiddenInGame(false);
		SetActorScale3D(FVector(GetActorScale3D().X, currentSize / rawSize.Y, 1.0f));
	}
}

//void ACoalStack::setGeometry(float position, float padLength, FVector padStart, FVector padEnd) {
//
//
//	FVector directionVector = (padEnd - padStart);
//	double targetDistance = (position/ padLength) * directionVector.Size(); // Get the distance we will be moving between the two vectors
//	directionVector.Normalize();
//	directionVector = directionVector * targetDistance;
//	SetActorLocation(padStart + directionVector);
//}

void ACoalStack::setWidth(float width) {
	SetActorScale3D(FVector(width/100.0f, GetActorScale3D().Y, 1.0f));
}


//// Set the coal stack to being a certian length by scaling relative to the length of the mesh
//void ACoalStack::setQuantity(float absoluteUELength) {
//
//	// input is in meters, we need to generate a value between 0 and 1.0 based on this absoluteUELength.
//
//	//const float meshLength = 400.0f;
//
//	//FVector origin;
//	//FVector extent;
//
//	//absoluteUELength / meshLength
//	if (absoluteUELength == 0.0f) {
//		SetActorHiddenInGame(true);
//	}
//	else {
//		SetActorHiddenInGame(false);
//	}
//	SetActorScale3D(FVector(GetActorScale3D().X, absoluteUELength/rawSize.Y, 1.0f));
//}

Stockpile::Id ACoalStack::getID() {
	return id;
}


