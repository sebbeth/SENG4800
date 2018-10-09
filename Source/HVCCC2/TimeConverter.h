// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TimeConverter.generated.h"


/**
 * 
 */
UCLASS()
class HVCCC2_API UTimeConverter : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "File Ops")
	static bool ConvertTime(bool totalTime, float hoursIn, float timeOffset, int& hoursOut, int& daysOut, int& weeksOut, FString& outputWD, FString& outputHM);

	static FString prepend(FString input);
	
	
};
