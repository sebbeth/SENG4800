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

	// Get the blueprints to be used
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AStackerReclaimer> largeSR_blueprint;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AStackerReclaimer> stacker_blueprint;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AStackerReclaimer> reclaimer_blueprint;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AShipLoader> ship_loader_blueprint;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AShip> ship_blueprint;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACoalStack> coal_stack_blueprint;

	// Koorigang Stacker Reclaimer track markers
	UPROPERTY(EditAnywhere)
		AActor *SR0_rail_start;
	UPROPERTY(EditAnywhere)
		AActor *SR0_rail_end;
	UPROPERTY(EditAnywhere)
		AActor *SR1_rail_start;
	UPROPERTY(EditAnywhere)
		AActor *SR1_rail_end;
	UPROPERTY(EditAnywhere)
		AActor *SR2_rail_start;
	UPROPERTY(EditAnywhere)
		AActor *SR2_rail_end;
	UPROPERTY(EditAnywhere)
		AActor *SR3_rail_start;
	UPROPERTY(EditAnywhere)
		AActor *SR3_rail_end;

	// Koorigang ship loader track markers
	UPROPERTY(EditAnywhere)
		AActor *loader0_rail_start;
	UPROPERTY(EditAnywhere)
		AActor *loader0_rail_end;
	UPROPERTY(EditAnywhere)
		AActor *loader1_rail_start;
	UPROPERTY(EditAnywhere)
		AActor *loader1_rail_end;
	UPROPERTY(EditAnywhere)
		AActor *loader2_rail_start;
	UPROPERTY(EditAnywhere)
		AActor *loader2_rail_end;
	UPROPERTY(EditAnywhere)
		AActor *loader3_rail_start;
	UPROPERTY(EditAnywhere)
		AActor *loader3_rail_end;

	// Ship berth position markers
	UPROPERTY(EditAnywhere)
		AActor *berth0_position;
	UPROPERTY(EditAnywhere)
		AActor *berth1_position;
	UPROPERTY(EditAnywhere)
		AActor *berth2_position;
	UPROPERTY(EditAnywhere)
		AActor *berth3_position;


	//Coal Pad position markers
	UPROPERTY(EditAnywhere)
		AActor *padK0_position;

private:

	AStackerReclaimer * spawnAReclaimer(FVector railStart, FVector railEnd, TSubclassOf<class AStackerReclaimer> blueprint);
	AShipLoader * spawnAShipLoader(FVector railStart, FVector railEnd, TSubclassOf<class AShipLoader> blueprint);
	AShip * spawnAShip(FVector position, FRotator rotator, TSubclassOf<class AShip> blueprint);
	ACoalStack * spawnACoalStack(FVector position, FRotator rotator, TSubclassOf<class ACoalStack> blueprint);


	int testTime; // Just being used for testing

};
