// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorSaveDto.h"
#include "BaseClasses/SerializerBase.h"
#include "ActorSerializer.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UESANDBOX_API UActorSerializer : public USerializerBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
		void Save(AActor* Actor, FActorSaveDto CameraSaveDto, bool& Success);

	UFUNCTION(BlueprintCallable)
		void Load(TArray<AActor*>& Actor, TArray<FActorSaveDto>& ActorSaveDto, bool& Success);

private:
	TArray<FActorSaveDto> ActorSaveDtoList;
};
