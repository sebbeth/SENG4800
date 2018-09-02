// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "scheduling/data/serialization.h"

#include "LevelController.generated.h"


UCLASS()
class HVCCC2_API ALevelController : public AActor
{
	GENERATED_BODY()
	
	StateMapTuple states;
	double xMin, xMax;

	//sliding windows peeking into the state-sequences of actors we are currently animating
	std::vector<std::pair<std::size_t, std::size_t>> windows;

	double worldTime;
	double speed;


	//AGlowCube *daCube;

	//AGlowCube * spawnAGlowCube(FVector start, FVector end);

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
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AConveyorBelt> conveyor_belt_blueprint;

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
	UPROPERTY(EditAnywhere)
		AActor *padK1_position;
	UPROPERTY(EditAnywhere)
		AActor *padK2_position;
	
	//actors
	UPROPERTY(EditAnywhere)
	TArray<ACoalStack*> coalStacks;
	UPROPERTY(EditAnywhere)
	TArray<AStackerReclaimer*> stackerReclaimers;
	UPROPERTY(EditAnywhere)
	TArray<AShipLoader*> shipLoaders;
	UPROPERTY(EditAnywhere)
	TArray<AShip*> ships;
	UPROPERTY(EditAnywhere)
	TArray<AConveyorBelt*> conveyorBelts;
private:

	AStackerReclaimer * spawnAReclaimer(FVector railStart, FVector railEnd, TSubclassOf<class AStackerReclaimer> blueprint);
	AShipLoader * spawnAShipLoader(FVector railStart, FVector railEnd, TSubclassOf<class AShipLoader> blueprint);
	AShip * spawnAShip(FVector position, FRotator rotator, TSubclassOf<class AShip> blueprint);
	AConveyorBelt* spawnAConveyorBelt(FVector position, FRotator rotator, TSubclassOf<class AConveyorBelt> blueprint);
	void spawnACoalStack(FVector position, FRotator rotator, TSubclassOf<class ACoalStack> blueprint);
	

	int testTime; // Just being used for testing

};
