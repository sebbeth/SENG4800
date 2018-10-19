// Fill out your copyright notice in the Description page of Project Settings.

#include "TrainTrackSpline.h"


// Sets default values
ATrainTrackSpline::ATrainTrackSpline()
{
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

