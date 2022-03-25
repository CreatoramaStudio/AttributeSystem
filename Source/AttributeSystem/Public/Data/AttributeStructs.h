// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/AttributeEnums.h"
#include "GameplayTagContainer.h"
#include "Delegates/AttributeDynamicDelegates.h"
#include "AttributeStructs.generated.h"

class UAttributeChanged;

USTRUCT(BlueprintType)
struct ATTRIBUTESYSTEM_API FAttribute
{
    GENERATED_BODY()


public:

    UPROPERTY(SaveGame, EditAnywhere)
        float BaseValue = 0;

    UPROPERTY(SaveGame, EditAnywhere)
        float Delta = 0;

    UPROPERTY(SaveGame, EditAnywhere)
        float Multiplier = 1;

    UPROPERTY(SaveGame, EditAnywhere)
        EFloatLimitType LimtType = EFloatLimitType::None;

    UPROPERTY(SaveGame, EditAnywhere, meta = (EditCondition = "LimtType==EFloatLimitType::Min", EditConditionHides))
        float MinLimitValue;

    UPROPERTY(SaveGame, EditAnywhere, meta = (EditCondition = "LimtType==EFloatLimitType::Max", EditConditionHides))
        float MaxLimitValue;

    UPROPERTY(SaveGame, EditAnywhere, meta = (EditCondition = "LimtType==EFloatLimitType::MinMax", EditConditionHides))
        FFloatInterval MinMaxLimitValues = FFloatInterval(0, 0);

    UPROPERTY()
    FOnUpdateAttibuteMulticast OnUpdateAttibute;

protected:  

private:

public:

    float GetValue() const
    {
        float Value = (BaseValue + Delta) * Multiplier;

        switch (LimtType)
        {
        case EFloatLimitType::None:
            return Value;
            break;

        case EFloatLimitType::Min:
            return FMath::Max(Value, MinLimitValue);
            break;

        case EFloatLimitType::Max:
            return FMath::Min(Value, MaxLimitValue);
            break;

        case EFloatLimitType::MinMax:
            return FMath::Clamp(Value, MinMaxLimitValues.Min, MinMaxLimitValues.Max);
            break;
        }

        return Value;
    }



protected:

private:

};