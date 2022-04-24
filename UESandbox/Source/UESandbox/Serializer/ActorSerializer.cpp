// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorSerializer.h"
#include "Engine/World.h"
#include "Serialization/BufferArchive.h"

void UActorSerializer::Save(AActor* Actor, FActorSaveDto ActorSaveDto, bool& Success)
{
	ActorSaveDtoList.Add(ActorSaveDto);
	Success = Save_Internal(Actor, ActorSaveDto.Data, ActorSaveDtoList);
}

void UActorSerializer::Load(TArray<AActor*>& ActorList, TArray<FActorSaveDto>& ActorSaveDtoList, bool& Success)
{
	Success = Load_Internal(ActorList, ActorSaveDtoList);
}
