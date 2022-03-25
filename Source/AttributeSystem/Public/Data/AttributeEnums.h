// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeEnums.generated.h"

UENUM(BlueprintType)
enum class EFloatLimitType : uint8
{
	None,
	Min,
	Max,
	MinMax,
};
