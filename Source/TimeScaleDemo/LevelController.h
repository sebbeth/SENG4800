// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "scheduling/data/serialization.h"
#include "GlowCube.h"
#include "LevelController.generated.h"

UCLASS()
class TIMESCALEDEMO_API ALevelController : public AActor
{
	GENERATED_BODY()
	//IMPORTANT: YOU MUST PLACE AN INSTANCE OF THIS IN YOUR 
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AGlowCube> glowCubeBlueprintToUse;
	StateMapTuple states;
	double xMin, xMax;

	std::pair<std::size_t, std::size_t> theWatch;

	double worldTime;
	double speed;

	AGlowCube *daCube;

	AGlowCube * spawnAGlowCube(FVector start, FVector end);

	void moveTime(double deltaTime);
public:	
	// Sets default values for this actor's properties
	ALevelController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	
};
