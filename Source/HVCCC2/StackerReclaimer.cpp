// Fill out your copyright notice in the Description page of Project Settings.

#include "StackerReclaimer.h"

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
	moveToPosition = 0;

	trackNodeA = FVector(-386690.0f, -200210.0f, -1430.0f);
	trackNodeB = FVector(-283360.0f, -130770.0f, -1430.0f);

	currentLocation = trackNodeA;
	SetActorLocation(currentLocation);

	targetLocation = trackNodeB;
	speed = 20.0f;   // change this to whatever

	
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

		currentLocation = this->GetActorLocation();
		//create a vector between the start position and end point 
		FVector directionVector = (targetLocation - currentLocation);

		//find the distance between the points
		double totalYDistance = directionVector.Size();

		//now we have the distance, we want the direction from start to end as a unit vector 
		directionVector.Normalize();

		//find the location that is timeScale along the path between the start and end points
		//FVector target = (currentLocation + directionVector * DeltaTime);
		FVector target = currentLocation + (directionVector * speed);
		//reposition the actor to the correct location
		SetActorLocation(target);
	}

		break;
	case 2:
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

void AStackerReclaimer::moveTo(int position) {
	state = 1;
	UE_LOG(LogTemp, Warning, TEXT("move"));

}

