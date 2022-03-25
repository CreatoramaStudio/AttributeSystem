// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AttributeDynamicDelegates.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnUpdateAttibute, FGameplayTag, AttributeTag, float, Value);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUpdateAttibuteMulticast, FGameplayTag, AttributeTag, float, Value);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUpdateAttibuteTagMulticast, bool, bAddedAttributeTag, FGameplayTag, ModifiedAttributeTag);


UENUM()
enum AAAA2
{
	A2
};