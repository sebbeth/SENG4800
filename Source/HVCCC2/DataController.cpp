// Fill out your copyright notice in the Description page of Project Settings.

#include "DataController.h"
#include "DataExtractor.h"
#include "stdafx.h"

#include <iostream>
#include <string>
#include <filesystem>

#include "DataStorageClasses/CCTShipLoaderLogEvent.h"
#include "DataStorageClasses/KCTReclaimerLogEvent.h"

namespace fs = std::experimental::filesystem;

// Sets default values
ADataController::ADataController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADataController::BeginPlay()
{
	Super::BeginPlay();
	
	DataExtractor dExtractor("C:/Users/Nick/Documents/Unreal Projects/XMLCodeTesting/Source/XMLCodeTesting/");

	vector<CCTShipLoaderLogEvent> dionteDemarcus = dExtractor.deserialize<CCTShipLoaderLogEvent>("CCTShipLoaderLog");

	UE_LOG(LogTemp, Warning, TEXT("Size of vector: %d"), dionteDemarcus.size());
}

// Called every frame
void ADataController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

