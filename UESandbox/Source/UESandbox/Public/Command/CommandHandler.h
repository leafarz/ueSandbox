// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CommandHandler.generated.h"

class UCommand;
/**
 *
 */
UCLASS(Blueprintable)
class UESANDBOX_API UCommandHandler : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "CommandHandler")
		bool HandleCommand(UCommand* Command);
};
