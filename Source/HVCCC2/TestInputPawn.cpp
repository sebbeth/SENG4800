// Fill out your copyright notice in the Description page of Project Settings.

#include "TestInputPawn.h"


// Sets default values
ATestInputPawn::ATestInputPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void ATestInputPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestInputPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestInputPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);


	InputComponent->BindAction("NextEvent", IE_Pressed, this, &ATestInputPawn::iterateSchedule);


}


void  ATestInputPawn::iterateSchedule() {

	UE_LOG(LogTemp, Warning, TEXT("Next"));

}
