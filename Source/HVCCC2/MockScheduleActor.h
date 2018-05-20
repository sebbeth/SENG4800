// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MockScheduleActor.generated.h"

UCLASS()
class HVCCC2_API AMockScheduleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMockScheduleActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int task;

	UFUNCTION(BlueprintCallable, Category = "Schedule")
	void iterateSchedule();
	
	
};
