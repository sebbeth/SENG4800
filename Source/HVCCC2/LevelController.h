// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "data/serialization.h"
#include "data/extraction/implementedEntities.h"

#include "LevelController.generated.h"


//specialise this for each entity, specifying the associated actor type
template<typename Entity>
struct UActorType {
	using type = void;
};
template<typename Entity, typename Actor= typename UActorType<Entity>::type>
using DataMap = std::map<
	typename Entity::Id,
	std::tuple<
		std::vector<typename Entity::AssociatedState>, //states
		std::pair<std::size_t, std::size_t>, //window into the states at current time
		Actor*, //UActor pointer
		bool //whether or not this actor is within render distance/needs to be updated
	>
>;

template<typename... Entities>
using DataMapTuple = std::tuple<StateMap<Entities>...>;

UCLASS()
class HVCCC2_API ALevelController : public AActor
{
	GENERATED_BODY()
	
	StateMapTuple<AllEntities> states;
	double xMin, xMax;

	//sliding windows peeking into the state-sequences of actors we are currently animating
	std::vector<std::pair<std::size_t, std::size_t>> windows;

	double simTime;
	double speed;
	bool isPlaying;
	
	//updates the windows etc according to the new time - note that setting times to something absolute may require resetting the sim instead of updating it updating the sim is near-constant in complexity, but resetting is not
	void updateSim();
public:	
	// Sets default values for this actor's properties
	ALevelController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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
		TSubclassOf<class ATrain> train_locomotive_blueprint;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACoalStack> coal_stack_blueprint;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AConveyorBelt> conveyor_belt_blueprint;

	// Koorigang Stacker Reclaimer track markers
	UPROPERTY(EditAnywhere)
		TArray<AActor*> NCT_SR_rails_start;
	UPROPERTY(EditAnywhere)
		TArray<AActor*> NCT_SR_rails_end;


	// Koorigang ship loader track markers
	UPROPERTY(EditAnywhere)
		TArray<AActor*> NCT_loader_rails_start;
	UPROPERTY(EditAnywhere)
		TArray<AActor*> NCT_loader_rails_end;

	// Ship berth position markers
	UPROPERTY(EditAnywhere)
		TArray<AActor*> NCT_berths;



	//Coal Pad position markers
	UPROPERTY(EditAnywhere)
		TArray<AActor*> NCT_pads;

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
		TArray<ATrain*> trains;
	UPROPERTY(EditAnywhere)
	TArray<AConveyorBelt*> conveyorBelts;

	//Conveyor Belt position markers
	UPROPERTY(EditAnywhere)
		AActor *conv1_position;
	UPROPERTY(EditAnywhere)
		AActor *conv2_position;

	//time controls
	UFUNCTION(BlueprintCallable, Category = "time")
	float getSimTime();
	UFUNCTION(BlueprintCallable, Category = "time")
	void setSimTime(float absoluteTime);
	UFUNCTION(BlueprintCallable, Category = "time")
	void moveSimTime(float deltaTime);
	UFUNCTION(BlueprintCallable, Category = "time")
	float getPlaySpeed();
	UFUNCTION(BlueprintCallable, Category = "time")
	void setPlaySpeed(float speed);

	//true if playing, false if paused
	UFUNCTION(BlueprintCallable, Category = "time")
	bool getPlayState();
	//true if playing, false if paused
	UFUNCTION(BlueprintCallable, Category = "time")
	void setPlayState(bool isPlaying);


	// Called every frame
	virtual void Tick(float DeltaTime) override;




private:

	AStackerReclaimer * spawnAStackerReclaimer(FString id, FVector railStart, FVector railEnd, TSubclassOf<class AStackerReclaimer> blueprint);
	AShipLoader * spawnAShipLoader(FString id, FVector railStart, FVector railEnd, TSubclassOf<class AShipLoader> blueprint);
	AShip * spawnAShip(FString id, FVector position, FRotator rotator, TSubclassOf<class AShip> blueprint);
	AConveyorBelt * spawnAConveyorBelt(FString id, FVector position, FRotator rotator, TSubclassOf<class AConveyorBelt> blueprint);
	ACoalStack * spawnACoalStack(FString id, FVector position, FRotator rotator, TSubclassOf<class ACoalStack> blueprint);
	ATrain * spawnATrain(FString id, FVector position, TSubclassOf<class ATrain> blueprint);

	void stackCoal(int stackerId);
	void stopStackingCoal(int stackerId);

	void reclaimCoal(int stackerId, int loaderId);
	void stopReclaimingCoal(int stackerId, int loaderId);


	// Helper functions, don't call these directy
	void setCoalStackingState(int stackerId, int state);
	void setCoalReclaimingState(int stackerId,int loaderId, int state);

	int testTime; // Just being used for testing

};
