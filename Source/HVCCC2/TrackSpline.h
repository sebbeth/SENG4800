// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Classes/Components/SplineComponent.h"
#include "Classes/Components/SplineMeshComponent.h"
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
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Track")
		void SetupSpline();

	UPROPERTY(EditDefaultsOnly, Category = "TrackMeshVar")
		 class UStaticMesh* TrackMesh;
	
	UPROPERTY(EditAnywhere, Category = "Track") //change to readOnly? dont really need it modified in bp?
		class USplineComponent* Spline;
	
 TArray< class USplineMeshComponent*> AddedSplineMeshComponents;
	
};
