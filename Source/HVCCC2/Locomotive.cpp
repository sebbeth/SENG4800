// Fill out your copyright notice in the Description page of Project Settings.

#include "Locomotive.h"


// Sets default values
ALocomotive::ALocomotive()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALocomotive::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALocomotive::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

