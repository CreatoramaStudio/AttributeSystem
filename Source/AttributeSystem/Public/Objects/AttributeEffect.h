// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AttributeEffect.generated.h"

class UAttributeComponent;

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class ATTRIBUTESYSTEM_API UAttributeEffect : public UObject
{
	GENERATED_BODY()

public:

protected:

	UPROPERTY()
		UAttributeComponent* AttributeComponent;

	UPROPERTY()
		AController* Controller;

private:

public:

	UAttributeEffect();

	virtual UWorld* GetWorld() const override;

	void InitializeVariables(UAttributeComponent* InAttributeComponent, AController* InController);

	UFUNCTION(BlueprintNativeEvent, Category = "Attribute Effect")
		void Construct();

	void ExecuteEffect();

	UFUNCTION(BlueprintCallable, Category = "Attribute Effect")
		void FinishEffect();

	UFUNCTION(BlueprintCallable, Category = "Attribute Effect")
		void CancelEffect();

protected:

	UFUNCTION(BlueprintNativeEvent, Category = "Attribute Effect")
		void StartEffect();

	UFUNCTION(BlueprintNativeEvent, Category = "Attribute Effect")
		void StopEffect(bool bCanceled);

	UFUNCTION(BlueprintPure, Category = "Attribute Effect")
		UAttributeComponent* GetAttributeComponent() const;

	UFUNCTION(BlueprintPure, Category = "Attribute Effect")
		AController* GetController() const;

	UFUNCTION(BlueprintPure, Category = "Attribute Effect")
		APawn* GetPawn() const;

private:

};
