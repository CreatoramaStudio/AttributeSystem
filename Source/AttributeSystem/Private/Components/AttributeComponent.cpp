// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AttributeComponent.h"

#include "LogAttributeSystem.h"
#include "Objects/AttributeEffect.h"

// Sets default values for this component's properties
UAttributeComponent::UAttributeComponent()
{

}

void UAttributeComponent::OnRegister()
{
	Super::OnRegister();

	if (GetOwner())
	{
		Controller = Cast<AController>(GetOwner());
	}
}


// Called when the game starts
void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	CreateDefaultAttributeEffects();
	
}

bool UAttributeComponent::HasAttribute(const FGameplayTag GameplayTag) const
{
	return Attributes.Contains(GameplayTag);
}


bool UAttributeComponent::GetAttributeValue(const FGameplayTag GameplayTag, float& Value) const
{
	if (const FAttribute* Attribute = Attributes.Find(GameplayTag))
	{
		Value = Attribute->GetValue();
		return true;
	}
	return false;
}

bool UAttributeComponent::AttributeHasLimit(const FGameplayTag GameplayTag) const
{
	if (const FAttribute* Attribute = Attributes.Find(GameplayTag))
	{
		return Attribute->HasLimit();
	}
	return false;
}

bool UAttributeComponent::GetAttributeBaseValue(const FGameplayTag GameplayTag, float& Value) const
{
	if (const FAttribute* Attribute = Attributes.Find(GameplayTag))
	{
		Value = Attribute->GetBaseValue();
		return true;
	}
	return false;
}

bool UAttributeComponent::GetAttributeDeltaValue(const FGameplayTag GameplayTag, float& Value) const
{
	if (const FAttribute* Attribute = Attributes.Find(GameplayTag))
	{
		Value = Attribute->Delta;
		return true;
	}
	return false;
}

bool UAttributeComponent::GetAttributeMultiplierValue(const FGameplayTag GameplayTag, float& Value) const
{
	if (const FAttribute* Attribute = Attributes.Find(GameplayTag))
	{
		Value = Attribute->Multiplier;
		return true;
	}
	return false;
}

bool UAttributeComponent::GetAttributeLimit(const FGameplayTag GameplayTag, EFloatLimitType& LimitType, float& MinLimitValue, float& MaxLimitValue) const
{
	if (const FAttribute* Attribute = Attributes.Find(GameplayTag))
	{
		LimitType = Attribute->LimitType;
		MinLimitValue = Attribute->LimitValues.Min;
		MaxLimitValue = Attribute->LimitValues.Max;
		return true;
	}
	return false;
}

bool UAttributeComponent::SetAttributeBaseValue(const FGameplayTag GameplayTag, const float Value)
{
	if (FAttribute* Attribute = Attributes.Find(GameplayTag))
	{
		Attribute->SetBaseValue(Value);

		ModifiedAttribute(Attribute,GameplayTag);

		return true;
	}
	return false;
}

bool UAttributeComponent::SetAttributeDeltaValue(const FGameplayTag GameplayTag, const float Value)
{
	if (FAttribute* Attribute = Attributes.Find(GameplayTag))
	{
		Attribute->Delta = Value;

		ModifiedAttribute(Attribute, GameplayTag);

		return true;
	}
	return false;
}

bool UAttributeComponent::SetAttributeMultiplierValue(const FGameplayTag GameplayTag, const float Value)
{
	if (FAttribute* Attribute = Attributes.Find(GameplayTag))
	{
		Attribute->Multiplier = Value;

		ModifiedAttribute(Attribute, GameplayTag);

		return true;
	}
	return false;
}

bool UAttributeComponent::SetAttributeLimitValues(const FGameplayTag GameplayTag, const EFloatLimitType LimitType, const float MinLimitValue, const float MaxLimitValue)
{
	if (FAttribute* Attribute = Attributes.Find(GameplayTag))
	{
		Attribute->LimitType = LimitType;
		Attribute->LimitValues.Min = MinLimitValue;
		Attribute->LimitValues.Max = MaxLimitValue;
		return true;
	}
	return false;
}

bool UAttributeComponent::AddAttributeBaseValue(const FGameplayTag GameplayTag, const float Value)
{
	if (const FAttribute* Attribute = Attributes.Find(GameplayTag))
	{
		SetAttributeBaseValue(GameplayTag, Attribute->GetBaseValue() + Value);

		return true;
	}
	return false;
}

bool UAttributeComponent::AddAttributeDeltaValue(const FGameplayTag GameplayTag, const float Value)
{
	if (const FAttribute* Attribute = Attributes.Find(GameplayTag))
	{
		SetAttributeDeltaValue(GameplayTag, Attribute->Delta + Value);

		return true;
	}
	return false;
}

bool UAttributeComponent::AddAttributeMultiplierValue(const FGameplayTag GameplayTag, const float Value)
{
	if (const FAttribute* Attribute = Attributes.Find(GameplayTag))
	{
		SetAttributeMultiplierValue(GameplayTag, Attribute->Multiplier + Value);

		return true;
	}
	return false;
}

bool UAttributeComponent::BindAttributeEvent(const FGameplayTag GameplayTag, const FOnUpdateAttribute& Value)
{
	if (FAttribute* Attribute = Attributes.Find(GameplayTag))
	{
		Attribute->OnUpdateAttribute.Add(Value);
		return true;
	}
	return false;
}

bool UAttributeComponent::UnbindAttributeEvent(const FGameplayTag GameplayTag, const FOnUpdateAttribute& Value)
{
	if (FAttribute* Attribute = Attributes.Find(GameplayTag))
	{
		Attribute->OnUpdateAttribute.Remove(Value);
		return true;
	}
	return false;
}

bool UAttributeComponent::UnbindAllAttributeEvents(const FGameplayTag GameplayTag, const FOnUpdateAttribute& Value)
{
	if (FAttribute* Attribute = Attributes.Find(GameplayTag))
	{
		Attribute->OnUpdateAttribute.Clear();
		return true;
	}
	return false;
}

TSet<UAttributeEffect*> UAttributeComponent::GetAttributeEffects() const
{
	return TSet<UAttributeEffect*>(AttributeEffects.Array());
}

bool UAttributeComponent::AddAttributeEffectByType(const TSubclassOf<UAttributeEffect> AttributeEffectType)
{
	if (AttributeEffectType)
	{
		for (const auto& AttributeEffect : AttributeEffects)
		{
			if (AttributeEffect->GetClass() == AttributeEffectType)
			{
				AttributeEffect->ExecuteEffect();
				return true;
			}
		}

		const TObjectPtr<UAttributeEffect> AttributeEffect = NewObject<UAttributeEffect>(Controller, AttributeEffectType);
		AttributeEffects.Add(AttributeEffect);
		AttributeEffect->InitializeVariables(this, Controller);
		AttributeEffect->Construct();
		AttributeEffect->ExecuteEffect();

		return true;
	}

	return false;
}

bool UAttributeComponent::RemoveAttributeEffectByType(const TSubclassOf<UAttributeEffect> AttributeEffectType)
{
	for (const auto& AttributeEffect : AttributeEffects)
	{
		if (AttributeEffect->GetClass() == AttributeEffectType)
		{
			AttributeEffect->FinishEffect();

			return true;
		}
	}

	return false;
}

bool UAttributeComponent::RemoveAllAttributeEffectByType(const TSubclassOf<UAttributeEffect> AttributeEffectType)
{
	for (const auto& AttributeEffect : AttributeEffects)
	{
		if (AttributeEffect->GetClass() == AttributeEffectType)
		{
			AttributeEffect->FinishAllEffects();

			return true;
		}
	}

	return false;
}

bool UAttributeComponent::RemoveAttributeEffect(const UAttributeEffect* AttributeEffect)
{
	if (AttributeEffects.Contains(AttributeEffect))
	{
		AttributeEffects.Remove(AttributeEffect);

		return true;
	}
	return false;
}

FString UAttributeComponent::GetAttributeTagsString() const
{
	return AttributeTags.ToString();
}

bool UAttributeComponent::AddAttributeTag(const FGameplayTag AttributeTag)
{
	if (!AttributeTags.HasTag(AttributeTag))
	{
		AttributeTags.AddTag(AttributeTag);
		ModifiedAttributeTag(true, AttributeTag);
		return true;
	}
	return false;
}

bool UAttributeComponent::RemoveAttributeTag(const FGameplayTag AttributeTag)
{
	if (AttributeTags.RemoveTag(AttributeTag))
	{
		ModifiedAttributeTag(false, AttributeTag);
		return true;
	}
	return false;
}

bool UAttributeComponent::HasAttributeTags(const FGameplayTag AttributeTag) const
{
	return AttributeTags.HasTag(AttributeTag);
}

bool UAttributeComponent::HasAnyAttributeTags(const FGameplayTagContainer OtherAttributeTags, const bool bExactMatch) const
{
	if (bExactMatch)
	{
		return AttributeTags.HasAnyExact(OtherAttributeTags);
	}
	return AttributeTags.HasAny(OtherAttributeTags);
}

bool UAttributeComponent::HasAllAttributeTags(const FGameplayTagContainer OtherAttributeTags, const bool bExactMatch) const
{
	if (bExactMatch)
	{
		return AttributeTags.HasAllExact(OtherAttributeTags);
	}
	return AttributeTags.HasAll(OtherAttributeTags);
}

bool UAttributeComponent::AttributeTagsMatchTagQuery(const FGameplayTagQuery TagQuery) const
{
	return AttributeTags.MatchesQuery(TagQuery);
}

void UAttributeComponent::ModifiedAttributeEffect(const bool bAddedAttributeTag, UAttributeEffect* AttributeEffect) const
{
	if (OnUpdateAttributeEffect.IsBound())
	{
		OnUpdateAttributeEffect.Broadcast(bAddedAttributeTag, AttributeEffect, AttributeEffect->GetStackSize());
	}
	
	const FString EffectState = bAddedAttributeTag ? "Added" : "Removed";
	FLogAttributeSystem::VisLogString(GetOwner(), EffectState + " Attribute Effect: " + AttributeEffect->GetName());
}

void UAttributeComponent::ModifiedAttribute(const FAttribute* Attribute, const FGameplayTag GameplayTag) const
{
	if (Attribute->OnUpdateAttribute.IsBound())
	{
		Attribute->OnUpdateAttribute.Broadcast(GameplayTag, Attribute->GetValue());
	}

	FLogAttributeSystem::VisLogString(GetOwner(),"Modified Attribute: " + GameplayTag.ToString() + " Value: " + FString::SanitizeFloat(Attribute->GetValue()));
}

void UAttributeComponent::ModifiedAttributeTag(const bool bAddedAttributeTag, const FGameplayTag AttributeTag) const
{
	if (OnUpdateAttributeTag.IsBound())
	{
		OnUpdateAttributeTag.Broadcast(bAddedAttributeTag, AttributeTag);
	}
	
	const FString TagState = bAddedAttributeTag ? "Added" : "Removed";
	FLogAttributeSystem::VisLogString(GetOwner(), TagState + " Attribute Tag: " + AttributeTag.ToString());
}

void UAttributeComponent::CreateDefaultAttributeEffects()
{
	AttributeEffects.Empty();

	for (const auto& AttributeEffectType : DefaultAttributeEffectTypes)
	{
		AddAttributeEffectByType(AttributeEffectType);
	}
}

