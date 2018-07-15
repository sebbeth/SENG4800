// Fill out your copyright notice in the Description page of Project Settings.

#include "DataController.h"
#include "Deserialisation code/ProjectSourceDir.h"
#include "Deserialisation code/DataExtractor.h"
#include "stdafx.h"

#include <iostream>
#include <string>
#include <filesystem>

#include "Deserialisation code/DataStorageClasses/CCTShipLoaderLogEvent.h"
#include "Deserialisation code/DataStorageClasses/KCTReclaimerLogEvent.h"

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
	
	//The class which holds the machine-dependent string pointing to the source folder of this project.
		//(NOTE: you will have to edit the string held withing ProjectSourceDir.cpp,
		//if you want the deserialisation functionality to work on your machine).
	ProjectSourceDir dir;

	DataExtractor dExtractor(dir.filePath);

	vector<CCTShipLoaderLogEvent> dionteDemarcus = dExtractor.deserialize<CCTShipLoaderLogEvent>("CCTShipLoaderLog");

	for (int i = 0; i < dionteDemarcus.size(); i++) {
		string str = dionteDemarcus.at(i).getEventName();
		FString fstr = UTF8_TO_TCHAR(str.c_str());

		UE_LOG(LogTemp, Warning, TEXT("%s"), *fstr);
	}

	UE_LOG(LogTemp, Warning, TEXT("The above is placeholder printouts to prove that the file is being deserialised"));
	UE_LOG(LogTemp, Warning, TEXT("and its contents are accessible in memory."));
}

// Called every frame
void ADataController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

