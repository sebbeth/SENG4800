// Fill out your copyright notice in the Description page of Project Settings.

#include "CoalStack.h"


// Sets default values
ACoalStack::ACoalStack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACoalStack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoalStack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Set the coal stack to being a certian percent filled, 0 = invisible, 1.0 = max length
void ACoalStack::setQuantity(float quantity) {

	SetActorScale3D(FVector(1.0f, quantity, 1.0f));
}


