// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Classes/Components/SplineComponent.h"
#include "TrainTrackSpline.generated.h"

UCLASS()
class HVCCC2_API ATrainTrackSpline : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrainTrackSpline();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Track") //change to readOnly? dont really need it modified in bp?
		class USplineComponent* Spline;

	UPROPERTY(EditAnywhere, Category = "Track")
		FString id;
	
	
};
