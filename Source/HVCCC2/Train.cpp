// Fill out your copyright notice in the Description page of Project Settings.

#include "Train.h"


// Sets default values
ATrain::ATrain()
{
 	 //Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//Our actors shouldn't tick
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATrain::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATrain::spawnCarriages(TSubclassOf<class AActor> blueprint, int count) {

	this->train_carriage_full_blueprint = blueprint;
	carriageCount = count;

	UWorld* world = GetWorld();
	if (world) {
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;


		for (int i = 0; i < carriageCount; i++)
		{
			AActor *actor = world->SpawnActor<AActor>(train_carriage_full_blueprint, GetActorLocation(), GetActorRotation(), spawnParams);
			carriages.Add(actor);
			actor->SetActorHiddenInGame(true);

		}
	}
}



void ATrain::setPosition(float position, USplineComponent* trackSpline) {

	auto makeTransform = FTransform(trackSpline->GetRotationAtDistanceAlongSpline(position, ESplineCoordinateSpace::World),
		trackSpline->GetLocationAtDistanceAlongSpline(position, ESplineCoordinateSpace::World),
		FVector(5.0f, 5.0f, 5.0f));


	if (currentTrackSpline == NULL) {
		currentTrackSpline = trackSpline;
	}
	if (trackSpline == previousTrackSpline) {
		currentTrackSpline = trackSpline;
		previousTrackSpline = NULL;
	}
	else {
		if (trackSpline != currentTrackSpline) {
			previousTrackSpline = currentTrackSpline;
			currentTrackSpline = trackSpline;
		}
	}


	

	SetActorTransform(makeTransform);

	for (int i = 0; i < carriages.Num(); i++) {

		float carraigePosition = position - (3400.0f * float(i + 1));
		if (carraigePosition > 0) {
			carriages[i]->SetActorHiddenInGame(false);
			
			

			auto carriageTransform = FTransform(trackSpline->GetRotationAtDistanceAlongSpline(carraigePosition, ESplineCoordinateSpace::World),
				trackSpline->GetLocationAtDistanceAlongSpline(carraigePosition, ESplineCoordinateSpace::World),
				FVector(5.0f, 5.0f, 5.0f));

			carriages[i]->SetActorTransform(carriageTransform);
		}
		else {
			if (previousTrackSpline == NULL) {
				carriages[i]->SetActorHiddenInGame(true);
			}
			else {
			
			//carriages[i]->SetActorHiddenInGame(true);

			// Put the carriage on the previous spline
			carraigePosition = previousTrackSpline->GetSplineLength() + position - (3400.0f * float(i + 1));
			
			auto carriageTransform = FTransform(previousTrackSpline->GetRotationAtDistanceAlongSpline(carraigePosition, ESplineCoordinateSpace::World),
				previousTrackSpline->GetLocationAtDistanceAlongSpline(carraigePosition, ESplineCoordinateSpace::World),
				FVector(5.0f, 5.0f, 5.0f));

			carriages[i]->SetActorTransform(carriageTransform);
			}
		}
	}	


	
}


void ATrain::hideTrain() {
	SetActorHiddenInGame(true);
	for (int i = 0; i < carriages.Num(); i++) {
		carriages[i]->SetActorHiddenInGame(true);
	}
}

void ATrain::showTrain() {
	SetActorHiddenInGame(false);
	for (int i = 0; i < carriages.Num(); i++) {
		carriages[i]->SetActorHiddenInGame(false);
	}
}


