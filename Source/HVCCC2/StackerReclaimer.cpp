// Fill out your copyright notice in the Description page of Project Settings.

#include "StackerReclaimer.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AStackerReclaimer::AStackerReclaimer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AStackerReclaimer::BeginPlay()
{
	Super::BeginPlay();
	FVector endOfTrack = trackNodeB - GetActorLocation();

	float foo =  FMath::Atan2(endOfTrack.Y, endOfTrack.X);
	float baseRotaton = 180 - FMath::RadiansToDegrees(FMath::Acos(foo));
	this->setBaseRotation(baseRotaton); //124
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


void AStackerReclaimer::resetRotation() {
	FRotator rotator = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), trackNodeB);
	setRotation(0);
}


void AStackerReclaimer::setBaseRotation(float degrees) {
	FRotator rotator(0.0f, degrees, 0.0f);
	SetActorRotation(rotator, ETeleportType::None);
}


void AStackerReclaimer::rotateMastToCoalStack(ACoalStack* coalStack) {
	


	int sign = -1;
	if (coalStack->GetActorLocation().Y > GetActorLocation().Y) {
		sign = 1;
	}

	if (coalStack->GetActorLocation().X > GetActorLocation().X) {
		setRotation(sign * 45);
	} else {
		setRotation(sign * 125);
	}


}


void AStackerReclaimer::setMaterial(int choice) {

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

