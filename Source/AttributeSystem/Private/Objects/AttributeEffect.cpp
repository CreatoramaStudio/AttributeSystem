// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/AttributeEffect.h"
#include "Components/AttributeComponent.h"

UAttributeEffect::UAttributeEffect()
{
}

UWorld* UAttributeEffect::GetWorld() const
{
	return nullptr;
}

void UAttributeEffect::InitializeVariables(UAttributeComponent* InAttributeComponent, AController* InController)
{
	AttributeComponent = InAttributeComponent;
	Controller = InController;
}

void UAttributeEffect::ExecuteEffect()
{
	StartEffect();
}

void UAttributeEffect::FinishEffect()
{
	StopEffect(false);

	if (AttributeComponent)
	{
		AttributeComponent->GetAttributeEffects().Remove(this);
	}
}

void UAttributeEffect::CancelEffect()
{
	StopEffect(true);

	if (AttributeComponent)
	{
		AttributeComponent->GetAttributeEffects().Remove(this);
	}
}

void UAttributeEffect::Construct_Implementation()
{
}

void UAttributeEffect::StartEffect_Implementation()
{
}

void UAttributeEffect::StopEffect_Implementation(bool bCanceled)
{
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
