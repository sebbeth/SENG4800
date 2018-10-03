// Fill out your copyright notice in the Description page of Project Settings.

#include "Ship.h"


// Sets default values
AShip::AShip()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AShip::BeginPlay()
{
	atSea();
	Super::BeginPlay();
}


void AShip::berthed() {
	SetActorHiddenInGame(false);

}
void AShip::atSea() {
	SetActorHiddenInGame(true);

}

