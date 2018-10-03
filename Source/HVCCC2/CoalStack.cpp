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
	
}


void ACoalStack::setPosition(float position, float trackLength, FVector trackStart, FVector trackEnd) {


	FVector directionVector = (trackEnd - trackStart);
	double targetDistance = (position/ trackLength) * directionVector.Size(); // Get the distance we will be moving between the two vectors
	directionVector.Normalize();
	directionVector = directionVector * targetDistance;
	SetActorLocation(trackStart + directionVector);
}

void ACoalStack::setWidth(float width) {
	SetActorScale3D(FVector(width/100.0f, GetActorScale3D().Y, 1.0f));
}


// Set the coal stack to being a certian percent filled, 0 = invisible, 1.0 = max length
void ACoalStack::setQuantity(float length) {

	// input is in meters, we need to generate a value between 0 and 1.0 based on this length.

	const float meshLength = 400.0f;

	SetActorScale3D(FVector(GetActorScale3D().X, length / meshLength, 1.0f));
}



