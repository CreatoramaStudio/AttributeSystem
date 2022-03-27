// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/AttributeStructs.h"
#include "GameplayTagContainer.h"
#include "AttributeComponent.generated.h"

class UAttributeEffect;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ATTRIBUTESYSTEM_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = "Attribute Component|Tag|Event")
		FOnUpdateAttibuteTagMulticast OnUpdateAttibuteTag;

protected:

	UPROPERTY(SaveGame, EditAnywhere, Category = "Attribute Component")
		TMap<FGameplayTag, FAttribute> Attributes;
	
	UPROPERTY(EditAnywhere, Category = "Attribute Component")
		TArray<TSubclassOf<UAttributeEffect>> DefaultAttributeEffectTypes;

	UPROPERTY(SaveGame)
		TArray<UAttributeEffect*> AttributeEffects;

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
		bool SetAttributeBaseValue(FGameplayTag GameplayTag,float Value);

	UFUNCTION(BlueprintCallable, Category = "Attribute Component|Attribute")
		bool SetAttributeDeltaValue(FGameplayTag GameplayTag, float Value);

	UFUNCTION(BlueprintCallable, Category = "Attribute Component|Attribute")
		bool SetAttributeMultiplierValue(FGameplayTag GameplayTag, float Value);

	UFUNCTION(BlueprintCallable, Category = "Attribute Component|Attribute")
		bool SetAttributeLimitValues(FGameplayTag GameplayTag, EFloatLimitType LimitType, float MinLimitValue, float MaxLimitValue);

	UFUNCTION(BlueprintCallable, Category = "Attribute Component|Attribute")
		bool AddAttributeBaseValue(FGameplayTag GameplayTag, float Value);

	UFUNCTION(BlueprintCallable, Category = "Attribute Component|Attribute")
		bool AddAttributeDeltaValue(FGameplayTag GameplayTag, float Value);

	UFUNCTION(BlueprintCallable, Category = "Attribute Component|Attribute")
		bool AddAttributeMultiplierValue(FGameplayTag GameplayTag, float Value);

	UFUNCTION(BlueprintCallable, Category = "Attribute Component|Attribute|Event")
		bool BindAttributeEvent(FGameplayTag GameplayTag, const FOnUpdateAttibute& Value);

	UFUNCTION(BlueprintCallable, Category = "Attribute Component|Attribute|Event")
		bool UnbindAttributeEvent(FGameplayTag GameplayTag, const FOnUpdateAttibute& Value);

	UFUNCTION(BlueprintCallable, Category = "Attribute Component|Attribute|Event")
		bool UnbindAllAttributeEvents(FGameplayTag GameplayTag, const FOnUpdateAttibute& Value);

	UFUNCTION(BlueprintPure, Category = "Attribute Component|Effect")
		TArray<UAttributeEffect*> GetAttributeEffects() const;

	UFUNCTION(BlueprintCallable, Category = "Attribute Component|Effect")
		bool AddAttributeEffect(TSubclassOf<UAttributeEffect> AttributeEffectType);

	UFUNCTION(BlueprintCallable, Category = "Attribute Component|Effect")
		bool RemoveAttributeEffect(TSubclassOf<UAttributeEffect> AttributeEffectType);

	UFUNCTION(BlueprintPure, Category = "Attribute Component|Tag")
		FString GetAttributeTagsString() const;

	UFUNCTION(BlueprintCallable, Category = "Attribute Component|Tag")
		bool AddAttributeTag(FGameplayTag AttributeTag);

	UFUNCTION(BlueprintCallable, Category = "Attribute Component|Tag")
		bool RemoveAttributeTag(FGameplayTag AttributeTag);

	UFUNCTION(BlueprintPure, Category = "Attribute Component|Tag")
		bool HasAttributeTags(FGameplayTag AttributeTag) const;

	UFUNCTION(BlueprintPure, Category = "Attribute Component|Tag")
		bool HasAnyAttributeTags(FGameplayTagContainer OtherAttributeTags,bool bExactMatch) const;

	UFUNCTION(BlueprintPure, Category = "Attribute Component|Tag")
		bool HasAllAttributeTags(FGameplayTagContainer OtherAttributeTags, bool bExactMatch) const;

	UFUNCTION(BlueprintPure, Category = "Attribute Component|Tag")
		bool AttributeTagsMatchTagQuery(FGameplayTagQuery TagQuery) const;

protected:

	void ModifiedAttribute(FAttribute* Attribute, FGameplayTag GameplayTag);

	void ModifiedAttributeTag(bool bAddedAttributeTag, FGameplayTag AttributeTag);

	virtual void CreateDefaultAttributeEffects();

private:
		
};
