// Fill out your copyright notice in the Description page of Project Settings.

#include "StackerReclaimer.h"


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

}

// Called every frame
void AStackerReclaimer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStackerReclaimer::test() {
	UE_LOG(LogTemp, Warning, TEXT("TEST"));

}

