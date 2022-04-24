// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Command.h"
#include "CommandHandler.h"
#include "UObject/UObjectIterator.h"
#include "GameFramework/Actor.h"
#include "CommandInvoker.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UESANDBOX_API ACommandInvoker : public AActor
{
	GENERATED_BODY()

public:
	/*
	 * Sends the command to its registered handler.
	 * Implementation is in blueprint.
	 */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "CommandInvoker")
		bool InvokeCommand(UCommand* Command);

	/*
	 * Method to register specific pair of command and handler.
	 * Implementation is in blueprint.
	 */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "CommandInvoker")
        bool RegisterHandler(TSubclassOf<class UCommand> Command, TSubclassOf<class UCommandHandler> CommandHandler);

	/*
	 * This method is intended to register all commands and their respective handlers.
	 * Implementation is in blueprint.
	 */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "CommandInvoker")
        bool RegisterHandlers();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CommandInvoker")
		TMap<UClass*, UCommandHandler*> Handlers;
};
