// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DebugHelper.generated.h"

/**
 * 
 */
UCLASS()
class UESANDBOX_API UDebugHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="DebugHelper", meta=(WorldContext="WorldContextObject", DevelopmentOnly))
	static void DrawDebugLineCustom(
		UObject* WorldContextObject,
		FVector Origin,
		FVector Direction = FVector::ForwardVector,
		float Length = 100.0,
		FLinearColor Color = FLinearColor::Red,
		float Duration = 0.0f,
		float Thickness = 2.0f);
	
	UFUNCTION(BlueprintCallable, Category="DebugHelper", meta=(WorldContext="WorldContextObject", DevelopmentOnly))
	static void DrawDebugSphereCustom(
		UObject* WorldContextObject,
		FVector Center,
		float Radius = 100.0,
		int32 Segments = 5,
		FLinearColor Color = FLinearColor::Red,
		float Duration = 0.0f,
		float Thickness = 1.0f);

	UFUNCTION(BlueprintCallable, Category="DebugHelper", meta=(WorldContext="WorldContextObject", DevelopmentOnly))
	static void DrawDirections(
		UObject* WorldContextObject,
		FVector Origin,
		FVector Forward = FVector::ForwardVector,
		FVector Up = FVector::UpVector,
		FVector Right = FVector::RightVector,
		float Length = 100.0,
		float Duration = 0.0f,
		float Thickness = 2.0f);

	UFUNCTION(BlueprintCallable, Category="DebugHelper", meta=(WorldContext="WorldContextObject", DevelopmentOnly))
	static void DrawDirections2(
		UObject* WorldContextObject,
		FVector Origin,
		FRotator Rotation,
		float Length = 100.0,
		float Duration = 0.0f,
		float Thickness = 2.0f);
};
