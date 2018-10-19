// Fill out your copyright notice in the Description page of Project Settings.

#include "ShipLoader.h"


// Sets default values
AShipLoader::AShipLoader()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShipLoader::BeginPlay()
{
	// On init, rotate the actor to be perpendicular to the rail
	FRotator rotator(0.0f, 35.0f, 0.0f);
	SetActorRotation(rotator, ETeleportType::None);
	
	Super::BeginPlay();
	
}

// Called every frame
void AShipLoader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShipLoader::setPosition(float position) {

	FVector directionVector = (trackNodeB - trackNodeA);
	double targetDistance = position * directionVector.Size(); // Get the distance we will be moving between the two vectors
	directionVector.Normalize();
	directionVector = directionVector * targetDistance;
	SetActorLocation(trackNodeA + directionVector);
}


void AShipLoader::setMaterial(int choice) {

	//IF 0 -> RED -> Conveyor Reclaiming
	//IF 1 -> RESET Material -> Grey
	//IF 2 -> BLUE -> Conveyor Stacking
	if (choice == 0) {
		ReclaimMaterial();
	}
	else if (choice == 1) {
		ResetMaterial();
	}
	else if (choice == 2) {
		StackMaterial();
	}



}