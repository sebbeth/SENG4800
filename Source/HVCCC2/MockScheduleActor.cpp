// Fill out your copyright notice in the Description page of Project Settings.

#include "MockScheduleActor.h"
#include "EngineUtils.h"
#include "StackerReclaimer.h"


// Sets default values
AMockScheduleActor::AMockScheduleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMockScheduleActor::BeginPlay()
{
	Super::BeginPlay();
	task = 0;


	int i = 0;



}


AStackerReclaimer* getStackerReclaimerAtIndex(int index, UWorld *world) {

	int i = 0;
	for (TActorIterator<AStackerReclaimer> ActorItr(world); ActorItr; ++ActorItr)
	{
		AStackerReclaimer *stackerReclaimer = *ActorItr;

		if (i == index) {
			return stackerReclaimer;
		}

		i++;
		
	}
	return NULL;
}

// Called every frame
void AMockScheduleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	



}

void AMockScheduleActor::iterateSchedule() {
		
	task++;
	UE_LOG(LogTemp, Warning, TEXT("schedule %d"), task);

	switch (task) {
	case 1:
	{	

		getStackerReclaimerAtIndex(0, GetWorld())->rotateTo(38.0f);
		getStackerReclaimerAtIndex(1, GetWorld())->moveTo(0.1f);
		getStackerReclaimerAtIndex(2, GetWorld())->moveTo(0.6);
		getStackerReclaimerAtIndex(3, GetWorld())->moveTo(0.2f);
		getStackerReclaimerAtIndex(4, GetWorld())->rotateTo(38.0f);
		getStackerReclaimerAtIndex(5, GetWorld())->rotateTo(38.0f);
		getStackerReclaimerAtIndex(6, GetWorld())->rotateTo(38.0f);
		getStackerReclaimerAtIndex(7, GetWorld())->moveTo(1.0f);

	}
		break;
	case 2:
	{

		getStackerReclaimerAtIndex(0, GetWorld())->rotateTo(38.0f);
		getStackerReclaimerAtIndex(4, GetWorld())->rotateTo(38.0f);
		getStackerReclaimerAtIndex(6, GetWorld())->moveTo(0.5f);
		getStackerReclaimerAtIndex(7, GetWorld())->moveTo(0.0f);
		getStackerReclaimerAtIndex(1, GetWorld())->rotateTo(38.0f);
		getStackerReclaimerAtIndex(2, GetWorld())->rotateTo(90.0);
		getStackerReclaimerAtIndex(5, GetWorld())->rotateTo(-90.0);

	}

	break;
	case 3:
	{

		getStackerReclaimerAtIndex(0, GetWorld())->moveTo(0);
		getStackerReclaimerAtIndex(6, GetWorld())->moveTo(0.7f);
		getStackerReclaimerAtIndex(4, GetWorld())->moveTo(0.0f);
		getStackerReclaimerAtIndex(1, GetWorld())->moveTo(0.0f);
		getStackerReclaimerAtIndex(3, GetWorld())->rotateTo(90.0);
		getStackerReclaimerAtIndex(5, GetWorld())->rotateTo(0.0);
		getStackerReclaimerAtIndex(2, GetWorld())->rotateTo(-90.0);
		getStackerReclaimerAtIndex(5, GetWorld())->rotateTo(38.0f);

	}
		break;
	case 4:
	
	{

		getStackerReclaimerAtIndex(5, GetWorld())->moveTo(0.0);
		getStackerReclaimerAtIndex(3, GetWorld())->moveTo(0.2f);
		getStackerReclaimerAtIndex(1, GetWorld())->moveTo(0.8f);
		getStackerReclaimerAtIndex(6, GetWorld())->moveTo(0.1f);
		getStackerReclaimerAtIndex(0, GetWorld())->rotateTo(30.0);
		getStackerReclaimerAtIndex(4, GetWorld())->rotateTo(-90.0);


	}


		break;

	case 5:
	{
		getStackerReclaimerAtIndex(3, GetWorld())->moveTo(0.7f);
		getStackerReclaimerAtIndex(1, GetWorld())->rotateTo(-90.0f);
		getStackerReclaimerAtIndex(6, GetWorld())->moveTo(0.3f);
		getStackerReclaimerAtIndex(2, GetWorld())->moveTo(1.0f);
		getStackerReclaimerAtIndex(4, GetWorld())->moveTo(1.0f);
		getStackerReclaimerAtIndex(5, GetWorld())->rotateTo(-90.0);
		getStackerReclaimerAtIndex(7, GetWorld())->moveTo(0.5f);


	}

	break;

	default:
		task = 1;
		break;
	};
}


