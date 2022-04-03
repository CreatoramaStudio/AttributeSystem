// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AttributeDynamicDelegates.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnUpdateAttribute, FGameplayTag, AttributeTag, float, Value);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUpdateAttributeMulticast, FGameplayTag, AttributeTag, float, Value);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUpdateAttributeTagMulticast, bool, bAddedAttributeTag, FGameplayTag, ModifiedAttributeTag);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUpdateAttributeEffectMulticast, bool, bAddedAttributeEffect, UAttributeEffect*, AttributeEffect, int32, StackSize);


UENUM()
enum AAAA2
{
	A2
};