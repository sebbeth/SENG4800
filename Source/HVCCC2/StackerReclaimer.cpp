// Fill out your copyright notice in the Description page of Project Settings.

#include "StackerReclaimer.h"
#include <cmath>
/*
state:
0 rest
1 moveto
2 rotate
*/

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
	
	state = 0;
	task = 0;
	moveToTarget = 0.0f;
	rotationTarget = 0.0f;
	rotationOffset = 32.8f;


	currentLocation = trackNodeA;
	SetActorLocation(currentLocation);

	targetLocation = trackNodeB;
	//maxSpeed = 80.0f;
	speed = maxSpeed;
}

// Called every frame
void AStackerReclaimer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	switch (state) {

	case 0:
		break;
	case 1:
	{
		speed = maxSpeed;
		currentLocation = this->GetActorLocation();
	
		FVector directionVector = (trackNodeB - trackNodeA);

		double targetDistance = moveToTarget * directionVector.Size();
		directionVector.Normalize();

		directionVector = directionVector * targetDistance;

		FVector targetVector = (trackNodeA + directionVector) - currentLocation;

		// Slow down and stop
		if (targetVector.Size() < 1000) {
			speed = speed / 2.0;
		}
		if (targetVector.Size() < 300) {
			speed = speed / 2.0;
		}
		if (targetVector.Size() < 200) {
			speed = 0;
			state = 0;
		}
		targetVector.Normalize();

	
		SetActorLocation( currentLocation + targetVector * speed);
	}

		break;
	case 2:

	{
		// Rotate
		FRotator currentRotation = this->GetActorRotation();
		float difference = abs(currentRotation.Yaw - rotationTarget);

		if (difference > 5) {
			if (currentRotation.Yaw > rotationTarget) {
				currentRotation.Yaw = currentRotation.Yaw - slewSpeed;
			}
			else {
				currentRotation.Yaw = currentRotation.Yaw + slewSpeed;
			}
			SetActorRotation(currentRotation, ETeleportType::None);

		} 
		else {
			state = 0;
		}
	}
		break;
	default:
		break;

	};


	
	//CurrentLocation.X += speed * DeltaTime; // use X Y or Z.  Use -= to go the opposite way

	/*
	UE_LOG(LogTemp, Warning, TEXT(" target is %s"),
		*target.ToString());
	UE_LOG(LogTemp, Warning, TEXT(" directionVector is %s"),
		*directionVector.ToString());

	UE_LOG(LogTemp, Warning, TEXT("time %f"),
		DeltaTime);
	*/
}


void AStackerReclaimer::moveTo(float position) {
	state = 1;
	moveToTarget = position;

}

void AStackerReclaimer::rotateTo(float degrees) {
	state = 2;
	rotationTarget = degrees;

}

