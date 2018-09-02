// Fill out your copyright notice in the Description page of Project Settings.

#include "StackerReclaimer.h"


// Sets default values
AStackerReclaimer::AStackerReclaimer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AStackerReclaimer::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AStackerReclaimer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


/* Set the actor's position along it's rail,
position 0 will place the actor at the start of the rail, 
and position 1.0 at the end.
*/
void AStackerReclaimer::setPosition(float position) {

	
	FVector directionVector = (trackNodeB - trackNodeA); 
	double targetDistance = position * directionVector.Size(); // Get the distance we will be moving between the two vectors
	directionVector.Normalize();
	directionVector = directionVector * targetDistance; 
	SetActorLocation(trackNodeA + directionVector);
}

void AStackerReclaimer::setRotation(float degrees) {
	FRotator rotator(0.0f, degrees, 0.0f);
	SetActorRotation(rotator, ETeleportType::None); 
}

