// Fill out your copyright notice in the Description page of Project Settings.

#include "ConveyorBelt.h"


// Sets default values
AConveyorBelt::AConveyorBelt()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	//setMaterial();

}

// Called when the game starts or when spawned
void AConveyorBelt::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AConveyorBelt::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AConveyorBelt::setMaterial() {

	ChangeMaterial();

}

