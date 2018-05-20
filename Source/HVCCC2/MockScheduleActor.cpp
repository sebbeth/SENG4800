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


	for (TActorIterator<AStackerReclaimer> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		AStackerReclaimer *Mesh = *ActorItr;
		//ClientMessage(ActorItr->GetName());
		//ClientMessage(ActorItr->GetActorLocation().ToString());
		//UE_LOG(LogTemp, Warning, TEXT("actor %s"), *ActorItr->GetName());

	}
}

// Called every frame
void AMockScheduleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (task) {
	case 0:
		//state = 0;
		break;
	case 1:
		//state = 1;

		break;
	case 2:
		//state = 2;
		break;
	case 3:
		//state = 1;
		break;

	default:
		//state = 0;
		break;
	};



}

void AMockScheduleActor::iterateSchedule() {
		
	task++;
	UE_LOG(LogTemp, Warning, TEXT("schedule %d"), task);


}


