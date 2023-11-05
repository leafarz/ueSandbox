// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaveDtoBase.generated.h"

USTRUCT(BlueprintType)
struct FSaveDtoBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
		FString ActorClassPath;

	UPROPERTY(BlueprintReadWrite)
		FString ActorName;

	UPROPERTY(BlueprintReadWrite)
		FTransform ActorTransform;

	TArray<uint8> Data;
};
