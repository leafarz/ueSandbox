// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BitOperations.generated.h"

/**
 * 
 */
UCLASS()
class UESANDBOX_API UBitOperations : public UObject
{
	GENERATED_BODY()

public:
	/* Combines 2 32-bit floats into 1 int32 in bytes form.
	 * Note: 32-bit floats will be converted to 16-bit floats in int32 (bits form).
	 *		 This will lose precision of the floats.
	*/
	UFUNCTION(BlueprintCallable)
		static int32 CombineFloats(float a, float b);
	
	/* Gets the 2 floats from values produced by CombineFloats()
	 * Parameter [a] is expected to be [FFloat16.encoded<<16][FFloat16.encoded].
	*/
	UFUNCTION(BlueprintCallable)
		static FVector2D DecomposeFloat(int32 a);
};
