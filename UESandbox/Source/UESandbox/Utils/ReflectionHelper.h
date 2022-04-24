// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ReflectionHelper.generated.h"

class UStaticMesh;
class UMaterial;
/**
 * 
 */
UCLASS()
class UESANDBOX_API UReflectionHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="ReflectionHelper")
        static void GetBlueprintsOfClass(TArray<TAssetSubclassOf<UObject>>& Subclasses, TSubclassOf<UObject> Base, bool bAllowAbstract, FString const& Path);

    UFUNCTION(BlueprintCallable, BlueprintPure)
        static FString GetActorClassPath(AActor* Actor);

    UFUNCTION(BlueprintCallable, BlueprintPure)
        static UStaticMesh* GetStaticMeshFromPath(FString Path);

    UFUNCTION(BlueprintCallable, BlueprintPure)
        static UMaterial* GetMaterialByPath(FString Path);
};
