// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "OpenDialog.generated.h"

/**
 * 
 */
UCLASS()
class HVCCC2_API UOpenDialog : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "File Ops")
	static bool ShowOpenFileDialog(FString InitialDir, FString Title, bool UseFilter, FString& Filepath);
	
	
};
