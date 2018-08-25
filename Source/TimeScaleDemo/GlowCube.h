// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/UMG/Public/Components/Slider.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GlowCube.generated.h"

UCLASS()
class TIMESCALEDEMO_API AGlowCube : public AActor
{
	GENERATED_BODY()
	
public:	
	static const double ANIMATION_DURATION;
	static const double STRAFE_SIN_REPETITIONS;
	static const double SCALE_SIN_REPETITIONS;
	static const double SIN_WAVE_HEIGHT;
	// Sets default values for this actor's properties
	AGlowCube();

public:
	FVector startPoint;
	FVector endPoint;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "GlowCube")
	void applyState(float delta);
};

//an implementation of the modulus operation that correctly wraps around when k is < 0
//this is useful for rewinding
double better_modulo(double a, double b);

/*
	UCLASS()
class FPSTEST_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIText)
	UTextBlock *CenterText;
	
};

Then Create the UserWidget Blueprint inheriting a class like this. Have the class object get the reference of the blueprint and then you can communicate with it

	@Cosmo, You would put something like this to get the reference

	UPROPERTY(EditDefaultsOnly, Category = Config)
	TSubclassOf<UCrosshairWidget> wCrossHair;

	You would also need a pointer reference as well

	if (wCrossHair)
	{
	APlayerController *PC = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PC)
	{
	CrosshairWidget = CreateWidget<UCrosshairWidget>(PC, wCrossHair);
	if (CrosshairWidget)
	{
	CrosshairWidget->AddToViewport();
	}
	}
	}
*/