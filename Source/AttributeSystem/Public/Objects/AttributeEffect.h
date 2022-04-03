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
	
	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite, Category = "Attribute Effect")
	FText Name;

protected:

	UPROPERTY(SaveGame)
		int32 StackSize = 0;

	UPROPERTY(SaveGame, EditAnywhere, Category = "Attribute Effect")
		bool bLimitStackSize = false;

	UPROPERTY(SaveGame, EditAnywhere, Category = "Attribute Effect", meta = (EditCondition = "bLimitStackSize", EditConditionHides))
		int32 MaxStackSize = 1;

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
		void FinishAllEffects();

	UFUNCTION(BlueprintPure, Category = "Attribute Effect")
		int32 GetStackSize() const;

	UFUNCTION(BlueprintPure, Category = "Attribute Effect")
		int32 GetMaxStackSize() const;

protected:

	void SetStackSize(int32 Value);

	void SetMaxStackSize(int32 Value);

	void AddStackSize(int32 Value);

	UFUNCTION(BlueprintNativeEvent, Category = "Attribute Effect")
		void AddEffect();

	UFUNCTION(BlueprintNativeEvent, Category = "Attribute Effect")
		void RemoveEffect();

	UFUNCTION(BlueprintPure, Category = "Attribute Effect")
		UAttributeComponent* GetAttributeComponent() const;

	UFUNCTION(BlueprintPure, Category = "Attribute Effect")
		AController* GetController() const;

	UFUNCTION(BlueprintPure, Category = "Attribute Effect")
		APawn* GetPawn() const;

private:

};
