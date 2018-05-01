// Fill out your copyright notice in the Description page of Project Settings.

#define M_PI 3.141592653589793238462643383279502884 /* pi */
#include "GlowCube.h"
#include <algorithm>
#include <iostream>
#include "Runtime/Engine/Classes/Engine/World.h"
const FVector AGlowCube::START_POINT(-425, -425, 50);
const FVector AGlowCube::END_POINT(425, 425, 50);
const double AGlowCube::ANIMATION_DURATION = 5; //5 seconds
const double AGlowCube::STRAFE_SIN_REPETITIONS = 2;
const double AGlowCube::SCALE_SIN_REPETITIONS = 1;
const double AGlowCube::SIN_WAVE_HEIGHT = 200;
// Sets default values
AGlowCube::AGlowCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	timeElapsed = 0;
}

// Called when the game starts or when spawned
void AGlowCube::BeginPlay()
{
	Super::BeginPlay();
	SetActorLocation(START_POINT);
	timeElapsed = 0;
	speed = 1;
}

// Called every frame
void AGlowCube::Tick(float DeltaTime)
{
	/*
		This is basically implemented by tracking the current point in the animation, and then using vector calculus to determine where the actor should be as an interpolation between the start and end positions of 
	*/
	Super::Tick(DeltaTime);
	
	//update the timeElapsed
	timeElapsed = better_modulo(timeElapsed+(DeltaTime*speed), ANIMATION_DURATION);
	
	//create a vector between the start position and end point 
	FVector directionVector = (END_POINT - START_POINT);

	//find the distance between the points
	double totalYDistance = directionVector.Size();
	
	//now we have the distance, we want the direction from start to end as a unit vector 
	directionVector.Normalize();

	//determine how far through the animation we are as a ratio
	double timeScale = (timeElapsed / ANIMATION_DURATION);

	//find the location that is timeScale along the path between the start and end points
	FVector target = (START_POINT + directionVector * (totalYDistance*timeScale));

	//the rest of this is just strafing the cube using a sin function; It's for show, don't worry too much about understanding it.

	//now add a sin wave, which shifts the cube perpendicular (orthogonal) to the existing directional vector, such that it strafes left and right as it travels
	FVector orthogonalDirection(-directionVector.Y, directionVector.X, directionVector.Z);

	//the value of the sin function at the current point in time
	double strafeSinValue = std::sin(timeScale*(M_PI*STRAFE_SIN_REPETITIONS));
	
	//calculate the strafe offset
	FVector strafeOffset = (orthogonalDirection * strafeSinValue)*SIN_WAVE_HEIGHT;
	
	//apply the offset to the target
	target += strafeOffset;

	//reposition the actor to the correct location
	SetActorLocation(target);

	//now do scaling
	//the value of the sin function at the current point in time
	double scaleSinValue = std::sin(timeScale*(M_PI*SCALE_SIN_REPETITIONS));

	double scaleResult = std::abs(scaleSinValue);
	SetActorScale3D(FVector(scaleResult, scaleResult, scaleResult));

	FRotator rotation(0, std::abs(scaleSinValue)*360, 0);
	//now do rotation
	SetActorRotation(rotation);
}

double better_modulo(double a, double b) {
	return std::fmod(std::fmod(a, b) + b, b);
}