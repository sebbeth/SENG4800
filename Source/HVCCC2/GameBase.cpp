// Fill out your copyright notice in the Description page of Project Settings.

#include "GameBase.h"




void AGameBase::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("WORLD"));

}