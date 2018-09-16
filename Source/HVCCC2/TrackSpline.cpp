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

	//ScoreTimeline = CreateDefaultSubobject<UTimelineComponent>(FName("TimelineScore"));

	//InterpFunction.BindUFunction(this, FName{ TEXT("TimelineFloatReturn") });

}



void ATrackSpline::SetupCurve()
{
	auto richCurve = new FRichCurve();
	auto key = richCurve->AddKey(0.0f, 0.0f); 
	richCurve->AddKey(200.0f, 5.0f);
	//richCurve->SetKeyTime(key, 10.0f);
	richCurve->SetKeyInterpMode(key, RCIM_Linear);
	
	fCurve = NewObject<UCurveFloat>();
	
	auto list = fCurve->GetCurves();
	list.Add(FRichCurveEditInfo(richCurve, FName{ TEXT("MyFirstCurve") }));
	

}
// Called when the game starts or when spawned
void ATrackSpline::BeginPlay()
{
	Super::BeginPlay();

	//ScoreTimeline->AddInterpFloat(fCurve, InterpFunction, FName{ TEXT("Floaty") });

	 // or PlayFromStart() etc, can be called anywhere in this class

	UWorld* world = GetWorld();
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;

	//blueprint.Get();
	FVector startPoint = Spline->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
	FRotator startRotation = Spline->GetRotationAtSplinePoint(0, ESplineCoordinateSpace::World);
	actor = world->SpawnActor<ATrain>(blueprint, startPoint, startRotation, spawnParams);

	//SetupCurve();
	//static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("/TestCurve"));
	//check(Curve.Succeeded());

	//fCurve = Curve.Object;

	if (fCurve)
	{

		FOnTimelineFloat onTimelineCallback;

		onTimelineCallback.BindUFunction(this, FName("TimelineCallback"));


		myTimeLine.AddInterpFloat(fCurve, onTimelineCallback, FName("Alpha"));


		myTimeLine.SetLooping(false);
		startPoint = Spline->GetLocationAtSplinePoint(1, ESplineCoordinateSpace::World);
		startRotation = Spline->GetRotationAtSplinePoint(1, ESplineCoordinateSpace::World);
		auto makeTransform = FTransform(startRotation, startPoint, FVector(1.0f, 1.0f, 1.0f));
		actor->SetActorTransform(makeTransform);

		myTimeLine.PlayFromStart();
	}
	
	
	
}


void ATrackSpline::TimelineFinishedCallback()
{
	// This function is called when the timeline finishes playing.
	UE_LOG(LogTemp, Warning, TEXT("time line has finished...."));
}

// Called every frame
void ATrackSpline::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("DeltaTime %f"), DeltaTime);
	myTimeLine.TickTimeline(DeltaTime);

	
	/*
	if (ScoreTimeline != NULL) 
	{ ScoreTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL); }
	*/
}

void ATrackSpline::TimelineCallback(float val)
{


	UE_LOG(LogTemp, Warning, TEXT("interpolatedVal: %f"), val);
	UE_LOG(LogTemp, Warning, TEXT("GetSplineLength: %f"), Spline->GetSplineLength());

	//This function is called for every tick in the timeline.
	float distance = Spline->GetSplineLength() * val;

	auto makeTransform = FTransform(Spline->GetRotationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World),
		Spline->GetLocationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World),
		FVector(1.0f, 1.0f, 1.0f));
	//ScoreTimeline->GetPlaybackPosition();

	//targets location = FMath::Lerp(actors location , splinelocation, interpolatedVal);

	//rotation, location, scale
	//auto makeTransform = FTransform(FMath::Lerp(actor->GetActorRotation(), Spline->GetRotationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World), interpolatedVal),
	//FMath::Lerp(actor->GetActorLocation(), Spline->GetLocationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World), interpolatedVal),
	//FVector(1.0f, 1.0f, 1.0f));
	//trainactor object SetWorldTransform(makeTransform)
	actor->SetActorTransform(makeTransform);//SetActorRelativeTransform(makeTransform);

	UE_LOG(LogTemp, Warning, TEXT("time line is running....  "));
	//	UE_LOG(LogTemp, Warning, TEXT("play rate: %f"  ), ScoreTimeline->GetPlayRate());
	//UE_LOG(LogTemp, Warning, TEXT("playbackpos: %f"  ), ScoreTimeline->GetPlaybackPosition());


	/*
	int i = 0;
	FVector location, actorLocation;
	FRotator rotation, actorRoation;
	for (i; i < Spline->GetSplineLength(); i++)
	{
	location = Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
	rotation = Spline->GetRotationAtSplinePoint(i, ESplineCoordinateSpace::World);

	actorLocation = actor->GetActorLocation();
	actorRoation = actor->GetActorRotation();

	actor->SetActorLocation(FMath::Lerp(location, actorLocation, interpolatedVal));
	actor->SetActorRotation(FMath::Lerp(rotation, actorRoation, interpolatedVal));

	}
	*/
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
		AddedSplineMeshComponents[Index]->AttachToComponent(Spline,FAttachmentTransformRules::SnapToTargetIncludingScale);
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

void ATrackSpline::moveTrain()
{
	int i = 0;
	FVector location, actorLocation;
	FRotator rotation, actorRoation;
	for (i; i < Spline->GetSplineLength(); i++)
	{
		location = Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
		rotation = Spline->GetRotationAtSplinePoint(i, ESplineCoordinateSpace::World);

		actorLocation = actor->GetActorLocation();
		actorRoation = actor->GetActorRotation();

		actor->SetActorLocation(FMath::Lerp(location, actorLocation, 0.5));
		actor->SetActorRotation(FMath::Lerp(rotation, actorRoation, 0.5));

	}
	//targets location = FMath::Lerp(actors location , ?, ScoreTimeline.GetPlaybackPosition());

}
void ATrackSpline::someMethod()
{
	if (fCurve != NULL)
	{
		FOnTimelineFloat onTimelineCallback;

		ScoreTimeline = NewObject<UTimelineComponent>(this, FName("TimelineAnimation"));
		ScoreTimeline->CreationMethod = EComponentCreationMethod::UserConstructionScript; // Indicate it comes from a blueprint so it gets cleared when we rerun construction scripts 
		this->BlueprintCreatedComponents.Add(ScoreTimeline); // Add to array so it gets saved 
		ScoreTimeline->SetNetAddressable();	// This component has a stable name that can be referenced for replication

		ScoreTimeline->SetPropertySetObject(this); // Set which object the timeline should drive properties on 
		ScoreTimeline->SetDirectionPropertyName(FName("TimelineDirection"));

		ScoreTimeline->SetLooping(false);
		ScoreTimeline->SetTimelineLength(5.0f);
		ScoreTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
		ScoreTimeline->SetPlaybackPosition(0.0f, false); //LogTimeline: SetPlaybackPosition: No float property 'None' in 'BP_Track_8'
														 //ScoreTimeline->SetPlayRate(0.5f);
														 //Add the float curve to the timeline and connect it to your timelines's interpolation function 
		onTimelineCallback.BindUFunction(this, FName{ TEXT("TimelineCallback") });
		onTimelineFinishedCallback.BindUFunction(this, FName{ TEXT("TimelineFinishedCallback") });
		ScoreTimeline->AddInterpFloat(fCurve, onTimelineCallback, FName("Alpha"));
		ScoreTimeline->SetTimelineFinishedFunc(onTimelineFinishedCallback);

		ScoreTimeline->RegisterComponent();
	}

	ScoreTimeline->PlayFromStart();

}


