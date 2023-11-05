// Fill out your copyright notice in the Description page of Project Settings.

#include "BitOperations.h"
#include "Float16.h"



int32 UBitOperations::CombineFloats(float a, float b)
{
	// convert 32-bit float to 16-bits
	FFloat16 _a = a;
	FFloat16 _b = b;

	// Note: Only tried little endian. Haven't tried big endian yet

	// get encoded values
	// [sign][exponent][mantissa] or [mantissa][exponent][sign]
	// depending on endianness
	uint16 _aConverted = _a.Encoded;
	uint16 _bConverted = _b.Encoded;

	return _aConverted << 16 | _bConverted;
}

FVector2D UBitOperations::DecomposeFloat(int32 a)
{
#if PLATFORM_LITTLE_ENDIAN
	FFloat16 _a = *(FFloat16*)(((char*)&a + 2));
	FFloat16 _b = *(FFloat16*)(&a);
#else
	FFloat16 _a = *(FFloat16*)(&a);
	FFloat16 _b = *(FFloat16*)(((char*)&a + 2));
#endif	
	return FVector2D(_a, _b);
}
