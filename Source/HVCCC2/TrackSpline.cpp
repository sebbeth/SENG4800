// Fill out your copyright notice in the Description page of Project Settings.

#include "TrackSpline.h"


// Sets default values
ATrackSpline::ATrackSpline() //: Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Spline = CreateDefaultSubobject<USplineComponent>(FName("testSpline"));
	TrackMesh = CreateDefaultSubobject<UStaticMesh>(FName("mesh"));
	//TrackMesh = NewObject<UStaticMesh>(this,FName("mesh"));
	//new(TrackMesh->SourceModels) FStaticMeshSourceModel();
	AddedSplineMeshComponents.Empty();
	
}

// Called when the game starts or when spawned
void ATrackSpline::BeginPlay()
{
	
	Super::BeginPlay();
	
}

// Called every frame
void ATrackSpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ATrackSpline::SetupSpline()
{
	int32 SplineMeshComponentsNum = AddedSplineMeshComponents.Num();

	//remove spline mesh components to get to Spline->GetNumSplinePoints() - 1
	for (int32 Index = SplineMeshComponentsNum - 1; Index >= Spline->GetNumberOfSplinePoints() - 1; --Index)
	{
		AddedSplineMeshComponents[Index]->DetachFromParent();
		AddedSplineMeshComponents[Index]->UnregisterComponent();
	}

	//remove entries from array or make room for new components
	AddedSplineMeshComponents.SetNum(Spline->GetNumberOfSplinePoints() - 1, true);

	//construct spline mesh components to get to Spline->GetNumSplinePoints() - 1
	//previously constructed components will remain in the AddedSplineMeshComponents array unchanged
	for (int32 Index = SplineMeshComponentsNum; Index < Spline->GetNumberOfSplinePoints() - 1; ++Index)
	{
		AddedSplineMeshComponents[Index] = NewObject<USplineMeshComponent>( this, USplineMeshComponent::StaticClass() );
	}

	//update components
	for (int32 Index = 0; Index < AddedSplineMeshComponents.Num(); ++Index)
	{
		AddedSplineMeshComponents[Index]->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		AddedSplineMeshComponents[Index]->SetMobility(EComponentMobility::Movable);
		AddedSplineMeshComponents[Index]->AttachTo(Spline);
			//AttachParent = Spline;

		AddedSplineMeshComponents[Index]->bCastDynamicShadow = false;
		AddedSplineMeshComponents[Index]->SetStaticMesh(TrackMesh);

		FVector pointLocationStart, pointTangentStart, pointLocationEnd, pointTangentEnd;
		Spline->GetLocalLocationAndTangentAtSplinePoint(Index, pointLocationStart, pointTangentStart);

		Spline->GetLocalLocationAndTangentAtSplinePoint(Index + 1, pointLocationEnd, pointTangentEnd);

		AddedSplineMeshComponents[Index]->SetStartAndEnd(pointLocationStart, pointTangentStart, pointLocationEnd, pointTangentEnd);
	}
	RegisterAllComponents();
}


