// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AttributeComponent.h"
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

bool UAttributeComponent::HasAttribute(FGameplayTag GameplayTag) const
{
	return Attributes.Contains(GameplayTag);
}


bool UAttributeComponent::GetAttributeValue(FGameplayTag GameplayTag, float& Value) const
{
	if (const FAttribute* Attribute = Attributes.Find(GameplayTag))
	{
		Value = Attribute->GetValue();
		return true;
	}
	return false;
}

bool UAttributeComponent::AttributeHasLimit(FGameplayTag GameplayTag) const
{
	if (const FAttribute* Attribute = Attributes.Find(GameplayTag))
	{
		return Attribute->HasLimit();
	}
	return false;
}

bool UAttributeComponent::GetAttributeBaseValue(FGameplayTag GameplayTag, float& Value) const
{
	if (const FAttribute* Attribute = Attributes.Find(GameplayTag))
	{
		Value = Attribute->BaseValue;
		return true;
	}
	return false;
}

bool UAttributeComponent::GetAttributeDeltaValue(FGameplayTag GameplayTag, float& Value) const
{
	if (const FAttribute* Attribute = Attributes.Find(GameplayTag))
	{
		Value = Attribute->Delta;
		return true;
	}
	return false;
}

bool UAttributeComponent::GetAttributeMultiplierValue(FGameplayTag GameplayTag, float& Value) const
{
	if (const FAttribute* Attribute = Attributes.Find(GameplayTag))
	{
		Value = Attribute->Multiplier;
		return true;
	}
	return false;
}

bool UAttributeComponent::GetAttributeLimit(FGameplayTag GameplayTag, EFloatLimitType& LimitType, float& MinLimitValue, float& MaxLimitValue) const
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

bool UAttributeComponent::SetAttributeBaseValue(FGameplayTag GameplayTag, float Value)
{
	if (FAttribute* Attribute = Attributes.Find(GameplayTag))
	{
		Attribute->BaseValue = Value;

		ModifiedAttribute(Attribute,GameplayTag);

		return true;
	}
	return false;
}

bool UAttributeComponent::SetAttributeDeltaValue(FGameplayTag GameplayTag, float Value)
{
	if (FAttribute* Attribute = Attributes.Find(GameplayTag))
	{
		Attribute->Delta = Value;

		ModifiedAttribute(Attribute, GameplayTag);

		return true;
	}
	return false;
}

bool UAttributeComponent::SetAttributeMultiplierValue(FGameplayTag GameplayTag, float Value)
{
	if (FAttribute* Attribute = Attributes.Find(GameplayTag))
	{
		Attribute->Multiplier = Value;

		ModifiedAttribute(Attribute, GameplayTag);

		return true;
	}
	return false;
}

bool UAttributeComponent::SetAttributeLimitValues(FGameplayTag GameplayTag, EFloatLimitType LimitType, float MinLimitValue, float MaxLimitValue)
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

bool UAttributeComponent::AddAttributeBaseValue(FGameplayTag GameplayTag, float Value)
{
	if (FAttribute* Attribute = Attributes.Find(GameplayTag))
	{
		SetAttributeBaseValue(GameplayTag, Attribute->BaseValue + Value);

		return true;
	}
	return false;
}

bool UAttributeComponent::AddAttributeDeltaValue(FGameplayTag GameplayTag, float Value)
{
	if (FAttribute* Attribute = Attributes.Find(GameplayTag))
	{
		SetAttributeDeltaValue(GameplayTag, Attribute->Delta + Value);

		return true;
	}
	return false;
}

bool UAttributeComponent::AddAttributeMultiplierValue(FGameplayTag GameplayTag, float Value)
{
	if (FAttribute* Attribute = Attributes.Find(GameplayTag))
	{
		SetAttributeMultiplierValue(GameplayTag, Attribute->Multiplier + Value);

		return true;
	}
	return false;
}

bool UAttributeComponent::BindAttributeEvent(FGameplayTag GameplayTag, const FOnUpdateAttibute& Value)
{
	if (FAttribute* Attribute = Attributes.Find(GameplayTag))
	{
		Attribute->OnUpdateAttibute.Add(Value);
		return true;
	}
	return false;
}

bool UAttributeComponent::UnbindAttributeEvent(FGameplayTag GameplayTag, const FOnUpdateAttibute& Value)
{
	if (FAttribute* Attribute = Attributes.Find(GameplayTag))
	{
		Attribute->OnUpdateAttibute.Remove(Value);
		return true;
	}
	return false;
}

bool UAttributeComponent::UnbindAllAttributeEvents(FGameplayTag GameplayTag, const FOnUpdateAttibute& Value)
{
	if (FAttribute* Attribute = Attributes.Find(GameplayTag))
	{
		Attribute->OnUpdateAttibute.Clear();
		return true;
	}
	return false;
}

TSet<UAttributeEffect*> UAttributeComponent::GetAttributeEffects() const
{
	return AttributeEffects;
}

bool UAttributeComponent::AddAttributeEffectByType(TSubclassOf<UAttributeEffect> AttributeEffectType)
{
	if (AttributeEffectType)
	{
		for (auto& AttributeEffect : AttributeEffects)
		{
			if (AttributeEffect->GetClass() == AttributeEffectType)
			{
				AttributeEffect->ExecuteEffect();
				return true;
			}
		}

		UAttributeEffect* AttributeEffect = NewObject<UAttributeEffect>(Controller, AttributeEffectType);
		AttributeEffects.Add(AttributeEffect);
		AttributeEffect->InitializeVariables(this, Controller);
		AttributeEffect->Construct();
		AttributeEffect->ExecuteEffect();

		return true;
	}

	return false;
}

bool UAttributeComponent::RemoveAttributeEffectByType(TSubclassOf<UAttributeEffect> AttributeEffectType)
{
	for (auto& AttributeEffect : AttributeEffects)
	{
		if (AttributeEffect->GetClass() == AttributeEffectType)
		{
			AttributeEffect->FinishEffect();

			return true;
		}
	}

	return false;
}

bool UAttributeComponent::RemoveAllAttributeEffectByType(TSubclassOf<UAttributeEffect> AttributeEffectType)
{
	for (auto& AttributeEffect : AttributeEffects)
	{
		if (AttributeEffect->GetClass() == AttributeEffectType)
		{
			AttributeEffect->FinishAllEffects();

			return true;
		}
	}

	return false;
}

bool UAttributeComponent::RemoveAttributeEffect(UAttributeEffect* AttributeEffect)
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

bool UAttributeComponent::AddAttributeTag(FGameplayTag AttributeTag)
{
	if (!AttributeTags.HasTag(AttributeTag))
	{
		AttributeTags.AddTag(AttributeTag);
		ModifiedAttributeTag(true, AttributeTag);
		return true;
	}
	return false;
}

bool UAttributeComponent::RemoveAttributeTag(FGameplayTag AttributeTag)
{
	if (AttributeTags.RemoveTag(AttributeTag))
	{
		ModifiedAttributeTag(false, AttributeTag);
		return true;
	}
	return false;
}

bool UAttributeComponent::HasAttributeTags(FGameplayTag AttributeTag) const
{
	return AttributeTags.HasTag(AttributeTag);
}

bool UAttributeComponent::HasAnyAttributeTags(FGameplayTagContainer OtherAttributeTags, bool bExactMatch) const
{
	if (bExactMatch)
	{
		return AttributeTags.HasAnyExact(AttributeTags);
	}
	return AttributeTags.HasAny(AttributeTags);
}

bool UAttributeComponent::HasAllAttributeTags(FGameplayTagContainer OtherAttributeTags, bool bExactMatch) const
{
	if (bExactMatch)
	{
		return AttributeTags.HasAllExact(AttributeTags);
	}
	return AttributeTags.HasAll(AttributeTags);
}

bool UAttributeComponent::AttributeTagsMatchTagQuery(FGameplayTagQuery TagQuery) const
{
	return AttributeTags.MatchesQuery(TagQuery);
}

void UAttributeComponent::ModifiedAttributeEffect(bool bAddedAttributeTag, UAttributeEffect* AttributeEffect)
{
	if (OnUpdateAttibuteEffect.IsBound())
	{
		OnUpdateAttibuteEffect.Broadcast(bAddedAttributeTag, AttributeEffect, AttributeEffect->GetStackSize());
	}
}

void UAttributeComponent::ModifiedAttribute(FAttribute* Attribute, FGameplayTag GameplayTag)
{
	if (Attribute->OnUpdateAttibute.IsBound())
	{
		Attribute->OnUpdateAttibute.Broadcast(GameplayTag, Attribute->GetValue());
	}
}

void UAttributeComponent::ModifiedAttributeTag(bool bAddedAttributeTag, FGameplayTag AttributeTag)
{
	if (OnUpdateAttibuteTag.IsBound())
	{
		OnUpdateAttibuteTag.Broadcast(bAddedAttributeTag, AttributeTag);
	}
}

void UAttributeComponent::CreateDefaultAttributeEffects()
{
	AttributeEffects.Empty();

	for (auto& AttributeEffectType : DefaultAttributeEffectTypes)
	{
		AddAttributeEffectByType(AttributeEffectType);
	}
}

