// Fill out your copyright notice in the Description page of Project Settings.

#include "TrainTrackSpline.h"


// Sets default values
ATrainTrackSpline::ATrainTrackSpline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	Spline = CreateDefaultSubobject<USplineComponent>(FName("RailWay"));
}

// Called when the game starts or when spawned
void ATrainTrackSpline::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrainTrackSpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

