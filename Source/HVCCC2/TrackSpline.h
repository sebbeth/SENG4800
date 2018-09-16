// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Classes/Components/SplineComponent.h"
#include "Classes/Components/SplineMeshComponent.h"
#include "Runtime/Engine/Classes/Components/TimelineComponent.h"

#include "GameFramework/Actor.h"
#include "Train.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Engine/World.h"

#include "Engine/StaticMesh.h"



#include "TrackSpline.generated.h"

UCLASS()
class HVCCC2_API ATrackSpline : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrackSpline();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void TimelineFinishedCallback();

	UFUNCTION()
		void TimelineCallback(float val);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Track")
		void SetupSpline();

	UFUNCTION(BlueprintCallable, Category = "Track")
		void someMethod();


	UFUNCTION()
		void moveTrain();
	
	UFUNCTION()
	void SetupCurve();

	UPROPERTY(EditDefaultsOnly, Category = "TrackMeshVar")
		 class UStaticMesh* TrackMesh;
	
	UPROPERTY(EditAnywhere, Category = "Track") //change to readOnly? dont really need it modified in bp?
		class USplineComponent* Spline;

	UPROPERTY(EditAnywhere, Category = "Train")
	TSubclassOf<class ATrain> blueprint;
	
	UPROPERTY(VisibleAnywhere, Category = "Track")
		UTimelineComponent* ScoreTimeline;

	UPROPERTY(EditAnywhere, Category = "Track")
		UCurveFloat* fCurve;

	UPROPERTY(VisibleAnywhere, Category = "Train")
		ATrain *actor;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<ETimelineDirection::Type> TimelineDirection;

	//UPROPERTY(VisibleAnyWhere)
		//float None;
	
	FTimeline myTimeLine;

		
	
		FOnTimelineEventStatic onTimelineFinishedCallback {};

	TArray< class USplineMeshComponent*> AddedSplineMeshComponents;


};
