// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

template<typename T>
struct FSaveCollectionDto
{
public:
	friend FArchive& operator<<(FArchive& Ar, FSaveCollectionDto& GameData)
	{
		Ar << GameData.SavedDto;
		return Ar;
	}

public:
	TArray<T> SavedDto;
};