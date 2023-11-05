// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "DebugHelper.h"

#include "Kismet/KismetMathLibrary.h"

void UDebugHelper::DrawDebugLineCustom(UObject* WorldContextObject, FVector Origin, FVector Direction, float Length, FLinearColor Color,
                                       float Duration, float Thickness)
{
#if ENABLE_DRAW_DEBUG
	DrawDebugLine(
		WorldContextObject->GetWorld(), Origin, Origin + Length * Direction.Normalize(),
		Color.ToFColor(true), false, Duration, SDPG_World, Thickness);
#endif
}

void UDebugHelper::DrawDebugSphereCustom(UObject* WorldContextObject, FVector Center, float Radius, int32 Segments, FLinearColor Color,
	float Duration, float Thickness)
{
#if ENABLE_DRAW_DEBUG
	DrawDebugSphere(
		WorldContextObject->GetWorld(), Center, Radius, Segments,
		Color.ToFColor(true), false, Duration, SDPG_World, Thickness);
#endif
}

void UDebugHelper::DrawDirections(UObject* WorldContextObject, FVector Origin, FVector Forward, FVector Up, FVector Right, float Length,
	float Duration, float Thickness)
{
#if ENABLE_DRAW_DEBUG
	DrawDebugLineCustom(WorldContextObject, Origin, Forward, Length, FColor::Red, Duration, Thickness);
	DrawDebugLineCustom(WorldContextObject, Origin, Up, Length, FColor::Blue, Duration, Thickness);
	DrawDebugLineCustom(WorldContextObject, Origin, Right, Length, FColor::Green, Duration, Thickness);
#endif
}

void UDebugHelper::DrawDirections2(UObject* WorldContextObject, FVector Origin, FRotator Rotation, float Length, float Duration, float Thickness)
{
#if ENABLE_DRAW_DEBUG
	DrawDirections(
		WorldContextObject, Origin,
		UKismetMathLibrary::GetForwardVector(Rotation),
		UKismetMathLibrary::GetUpVector(Rotation),
		UKismetMathLibrary::GetRightVector(Rotation),
		Length, Duration, Thickness);
#endif
}
