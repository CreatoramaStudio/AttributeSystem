// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/AttributeEnums.h"
#include "GameplayTagContainer.h"
#include "Delegates/AttributeDynamicDelegates.h"
#include "AttributeStructs.generated.h"

USTRUCT(BlueprintType)
struct ATTRIBUTESYSTEM_API FAttribute
{
    GENERATED_BODY()

protected:

    UPROPERTY(SaveGame, EditAnywhere)
        float BaseValue = 0;

public:

    UPROPERTY(SaveGame, EditAnywhere)
        float Delta = 0;

    UPROPERTY(SaveGame, EditAnywhere)
        float Multiplier = 1;

    UPROPERTY(SaveGame, EditAnywhere)
        EFloatLimitType LimitType = EFloatLimitType::None;

    UPROPERTY(SaveGame, EditAnywhere, meta = (EditCondition = "LimitType!=EFloatLimitType::None", EditConditionHides))
        FFloatInterval LimitValues = FFloatInterval(0, 0);

    UPROPERTY(SaveGame)
        FOnUpdateAttributeMulticast OnUpdateAttibute;

protected:

private:

public:

    void SetBaseValue(float Value)
    {
        switch (LimitType)
        {
        case EFloatLimitType::None:
            BaseValue = Value;
            break;
        case EFloatLimitType::Min:
            BaseValue = FMath::Max(Value, LimitValues.Min);
            break;
        case EFloatLimitType::Max:
            BaseValue = FMath::Min(Value, LimitValues.Max);
            break;
        case EFloatLimitType::MinMax:
            BaseValue = FMath::Clamp(Value, LimitValues.Min, LimitValues.Max);
            break;
        }
    }

    float GetBaseValue() const
    {
        return BaseValue;
    }

    float GetValue() const
    {
        float Value = (BaseValue + Delta) * Multiplier;

        switch (LimitType)
        {
        case EFloatLimitType::None:
            return Value;
            break;

        case EFloatLimitType::Min:
            return FMath::Max(Value, LimitValues.Min);
            break;

        case EFloatLimitType::Max:
            return FMath::Min(Value, LimitValues.Max);
            break;

        case EFloatLimitType::MinMax:
            return FMath::Clamp(Value, LimitValues.Min, LimitValues.Max);
            break;
        }

        return Value;
    }

    bool HasLimit() const
    {
        return LimitType != EFloatLimitType::None;
    }


protected:

private:

};