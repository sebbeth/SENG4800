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

// Called every frame
void ATrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ATrain::setPosition(float position) {



}


