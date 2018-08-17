// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelController.generated.h"

UCLASS()
class HVCCC2_API ALevelController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AStackerReclaimer> largeSR_blueprint;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AStackerReclaimer> stacker_blueprint;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AStackerReclaimer> reclaimer_blueprint;


private:

	AStackerReclaimer* spawnAReclaimer(FVector railStart, FVector railEnd, TSubclassOf<class AStackerReclaimer> blueprint);
	
	AStackerReclaimer *stackerReclaimers[4];
	
};
