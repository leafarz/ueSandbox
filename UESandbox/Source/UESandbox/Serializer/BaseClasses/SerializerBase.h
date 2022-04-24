// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BufferArchive.h"
#include "FileHelper.h"
#include "MemoryReader.h"
#include "MemoryWriter.h"
#include "SaveCollectionDto.h"
#include "SaveGameArchive.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "UObject/NoExportTypes.h"
#include "SerializerBase.generated.h"

/**
 * 
 */
UCLASS()
class UESANDBOX_API USerializerBase : public UObject
{
	GENERATED_BODY()

protected:
	template<typename T>
	bool Save_Internal(AActor* Actor, TArray<uint8>& Data, TArray<T>& SavedDto)
	{
		FMemoryWriter MemoryWriter(Data, true);
		FSaveGameArchive Ar(MemoryWriter);
		Actor->Serialize(Ar);

		FSaveCollectionDto<T> CollectionDto;
		CollectionDto.SavedDto = SavedDto;

		FBufferArchive BinaryData;
		BinaryData << CollectionDto;

		bool Success = FFileHelper::SaveArrayToFile(BinaryData, *SaveFileName);
		BinaryData.FlushCache();
		BinaryData.Empty();

		if (Success)
		{
			UE_LOG(LogTemp, Warning, TEXT("Save Success! %s"), FPlatformProcess::BaseDir());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Save Failed!"));
		}

		return Success;
	}

	template<typename T>
	bool Load_Internal(TArray<AActor*>& ActorList, TArray<T>& SaveDtoList)
	{
		TArray<uint8> BinaryData;
		if (!FFileHelper::LoadFileToArray(BinaryData, *SaveFileName))
		{
			return false;
		}

		FMemoryReader FromBinary = FMemoryReader(BinaryData, true);
		FromBinary.Seek(0);

		FSaveCollectionDto<T> SaveCollectionDto;
		FromBinary << SaveCollectionDto;

		FromBinary.FlushCache();
		BinaryData.Empty();
		FromBinary.Close();

		SaveDtoList = SaveCollectionDto.SavedDto;
		for (FSaveDtoBase ActorRecord : SaveCollectionDto.SavedDto)
		{
			FVector SpawnPos = ActorRecord.ActorTransform.GetLocation();
			FRotator SpawnRot = ActorRecord.ActorTransform.Rotator();
			FActorSpawnParameters SpawnParams;
			SpawnParams.Name = FName(*ActorRecord.ActorName);
			UClass* SpawnClass = FindObject<UClass>(ANY_PACKAGE, *ActorRecord.ActorClassPath);
			if (SpawnClass)
			{
				AActor* NewActor = GWorld->SpawnActor(SpawnClass, &SpawnPos, &SpawnRot, SpawnParams);
				NewActor->SetActorLabel(ActorRecord.ActorName);
				ActorList.Add(NewActor);
			}
		}

		return true;
	}

public:
	UPROPERTY(BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
		FString SaveFileName = "Test.sav";
};
