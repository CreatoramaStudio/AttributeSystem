// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/AttributeStructs.h"
#include "GameplayTagContainer.h"
#include "AttributeComponent.generated.h"

class UAttributeEffect;

UCLASS( ClassGroup=(Attribute), meta=(BlueprintSpawnableComponent) )
class ATTRIBUTESYSTEM_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(SaveGame,BlueprintAssignable, Category = "Attribute Component|Tag|Event")
	FOnUpdateAttributeTagMulticast OnUpdateAttributeTag;

	UPROPERTY(SaveGame,BlueprintAssignable, Category = "Attribute Component|Tag|Event")
	FOnUpdateAttributeEffectMulticast OnUpdateAttributeEffect;

protected:

	UPROPERTY(SaveGame, EditAnywhere, Category = "Attribute Component")
	TMap<FGameplayTag, FAttribute> Attributes;

	UPROPERTY(EditAnywhere, Category = "Attribute Component")
	TArray<TSubclassOf<UAttributeEffect>> DefaultAttributeEffectTypes;

	UPROPERTY(SaveGame)
	TSet<UAttributeEffect*> AttributeEffects;

	UPROPERTY(SaveGame, EditAnywhere, Category = "Attribute Component")
	FGameplayTagContainer AttributeTags;

	UPROPERTY()
	AController* Controller;

private:

public:

	// Sets default values for this component's properties
	UAttributeComponent();

	virtual void OnRegister() override;

	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure, Category = "Attribute Component|Attribute")
	bool HasAttribute(FGameplayTag GameplayTag) const;

	UFUNCTION(BlueprintPure, Category = "Attribute Component|Attribute")
	bool GetAttributeValue(FGameplayTag GameplayTag, float& Value) const;

	UFUNCTION(BlueprintPure, Category = "Attribute Component|Attribute")
	bool AttributeHasLimit(FGameplayTag GameplayTag) const;

	UFUNCTION(BlueprintPure, Category = "Attribute Component|Attribute")
	bool GetAttributeBaseValue(FGameplayTag GameplayTag, float& Value) const;

	UFUNCTION(BlueprintPure, Category = "Attribute Component|Attribute")
	bool GetAttributeDeltaValue(FGameplayTag GameplayTag, float& Value) const;

	UFUNCTION(BlueprintPure, Category = "Attribute Component|Attribute")
	bool GetAttributeMultiplierValue(FGameplayTag GameplayTag, float& Value) const;

	UFUNCTION(BlueprintPure, Category = "Attribute Component|Attribute")
	bool GetAttributeLimit(FGameplayTag GameplayTag, EFloatLimitType& LimitType, float& MinLimitValue, float& MaxLimitValue) const;

	UFUNCTION(BlueprintCallable, Category = "Attribute Component|Attribute")
	bool SetAttributeBaseValue(FGameplayTag GameplayTag, float Value);

	UFUNCTION(BlueprintCallable, Category = "Attribute Component|Attribute")
	bool SetAttributeDeltaValue(FGameplayTag GameplayTag, float Value);

	UFUNCTION(BlueprintCallable, Category = "Attribute Component|Attribute")
	bool SetAttributeMultiplierValue(FGameplayTag GameplayTag, float Value);

	UFUNCTION(BlueprintCallable, Category = "Attribute Component|Attribute")
	bool SetAttributeLimitValues(const FGameplayTag GameplayTag, EFloatLimitType LimitType, float MinLimitValue, float MaxLimitValue);

	UFUNCTION(BlueprintCallable, Category = "Attribute Component|Attribute")
	bool AddAttributeBaseValue(const FGameplayTag GameplayTag, const float Value);

	UFUNCTION(BlueprintCallable, Category = "Attribute Component|Attribute")
	bool AddAttributeDeltaValue(const FGameplayTag GameplayTag, const float Value);

	UFUNCTION(BlueprintCallable, Category = "Attribute Component|Attribute")
	bool AddAttributeMultiplierValue(const FGameplayTag GameplayTag, const float Value);

	UFUNCTION(BlueprintCallable, Category = "Attribute Component|Attribute|Event")
	bool BindAttributeEvent(const FGameplayTag GameplayTag, const FOnUpdateAttribute& Value);

	UFUNCTION(BlueprintCallable, Category = "Attribute Component|Attribute|Event")
	bool UnbindAttributeEvent(const FGameplayTag GameplayTag, const FOnUpdateAttribute& Value);

	UFUNCTION(BlueprintCallable, Category = "Attribute Component|Attribute|Event")
	bool UnbindAllAttributeEvents(const FGameplayTag GameplayTag, const FOnUpdateAttribute& Value);

	UFUNCTION(BlueprintPure, Category = "Attribute Component|Effect")
	TSet<UAttributeEffect*> GetAttributeEffects() const;

	UFUNCTION(BlueprintCallable, Category = "Attribute Component|Effect")
	bool AddAttributeEffectByType(const TSubclassOf<UAttributeEffect> AttributeEffectType);

	UFUNCTION(BlueprintCallable, Category = "Attribute Component|Effect")
	bool RemoveAttributeEffectByType(const TSubclassOf<UAttributeEffect> AttributeEffectType);

	UFUNCTION(BlueprintCallable, Category = "Attribute Component|Effect")
	bool RemoveAllAttributeEffectByType(const TSubclassOf<UAttributeEffect> AttributeEffectType);

	bool RemoveAttributeEffect(const UAttributeEffect* AttributeEffect);

	UFUNCTION(BlueprintPure, Category = "Attribute Component|Tag")
	FString GetAttributeTagsString() const;

	UFUNCTION(BlueprintCallable, Category = "Attribute Component|Tag")
	bool AddAttributeTag(const FGameplayTag AttributeTag);

	UFUNCTION(BlueprintCallable, Category = "Attribute Component|Tag")
	bool RemoveAttributeTag(const FGameplayTag AttributeTag);

	UFUNCTION(BlueprintPure, Category = "Attribute Component|Tag")
	bool HasAttributeTags(const FGameplayTag AttributeTag) const;

	UFUNCTION(BlueprintPure, Category = "Attribute Component|Tag")
	bool HasAnyAttributeTags(FGameplayTagContainer OtherAttributeTags, const bool bExactMatch) const;

	UFUNCTION(BlueprintPure, Category = "Attribute Component|Tag")
	bool HasAllAttributeTags(FGameplayTagContainer OtherAttributeTags, const bool bExactMatch) const;

	UFUNCTION(BlueprintPure, Category = "Attribute Component|Tag")
	bool AttributeTagsMatchTagQuery(const FGameplayTagQuery TagQuery) const;

	void ModifiedAttributeEffect(const bool bAddedAttributeTag, UAttributeEffect* AttributeEffect) const;

protected:

	void ModifiedAttribute(const FAttribute* Attribute,const FGameplayTag GameplayTag) const;

	void ModifiedAttributeTag(const bool bAddedAttributeTag,const FGameplayTag AttributeTag) const;

	virtual void CreateDefaultAttributeEffects();

private:
};
