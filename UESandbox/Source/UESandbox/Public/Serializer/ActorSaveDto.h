// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseClasses/SaveDtoBase.h"
#include "ActorSaveDto.generated.h"

USTRUCT(BlueprintType)
struct FActorSaveDto : public FSaveDtoBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
		FString StaticMeshPath;

	UPROPERTY(BlueprintReadWrite)
		FString StaticMeshMaterialPath;

	friend FArchive& operator <<(FArchive& Ar, FActorSaveDto& CameraData)
	{
		Ar << CameraData.ActorClassPath;
		Ar << CameraData.ActorName;
		Ar << CameraData.ActorTransform;
		Ar << CameraData.StaticMeshPath;
		Ar << CameraData.StaticMeshMaterialPath;
		Ar << CameraData.Data;
		return Ar;
	}
};
