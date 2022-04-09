// Fill out your copyright notice in the Description page of Project Settings.

#include "Objects/AttributeEffect.h"
#include "Components/AttributeComponent.h"

UAttributeEffect::UAttributeEffect()
{
	StackSize = 0;
}

UWorld* UAttributeEffect::GetWorld() const
{
	return nullptr;
}

void UAttributeEffect::InitializeVariables(TObjectPtr<UAttributeComponent> InAttributeComponent, TObjectPtr<AController> InController)
{
	AttributeComponent = InAttributeComponent;
	Controller = InController;
}

void UAttributeEffect::ExecuteEffect()
{
	AddStackSize(1);
}

void UAttributeEffect::FinishEffect()
{
	AddStackSize(-1);
}

void UAttributeEffect::FinishAllEffects()
{
	for (int32 i = 0; i <= StackSize; ++i)
	{
		FinishEffect();
	}
}

void UAttributeEffect::SetStackSize(const int32 Value)
{
	const int32 OldValue = StackSize;
	StackSize = bLimitStackSize ? FMath::Clamp(Value, 0, MaxStackSize) : Value;

	if (AttributeComponent)
	{
		if (StackSize > OldValue)
		{
			AddEffect();
			AttributeComponent->ModifiedAttributeEffect(true, this);
		}
		else if(StackSize < OldValue)
		{
			RemoveEffect();
			AttributeComponent->ModifiedAttributeEffect(false, this);
		}

		if (StackSize <= 0)
		{
			AttributeComponent->RemoveAttributeEffect(this);
		}
	}
	
}

void UAttributeEffect::SetMaxStackSize(const int32 Value)
{
	MaxStackSize = FMath::Min(1, Value);
}

void UAttributeEffect::AddStackSize(const int32 Value)
{
	SetStackSize(StackSize + Value);
}

void UAttributeEffect::Construct_Implementation()
{
}

void UAttributeEffect::AddEffect_Implementation()
{
}

void UAttributeEffect::RemoveEffect_Implementation()
{
}

int32 UAttributeEffect::GetStackSize() const
{
	return StackSize;
}

int32 UAttributeEffect::GetMaxStackSize() const
{
	return MaxStackSize;
}

UAttributeComponent* UAttributeEffect::GetAttributeComponent() const
{
	return AttributeComponent;
}

AController* UAttributeEffect::GetController() const
{
	return Controller;
}

APawn* UAttributeEffect::GetPawn() const
{
	return Controller->GetPawn();
}
