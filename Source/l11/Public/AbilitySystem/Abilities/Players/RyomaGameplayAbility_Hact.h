// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/BaseAttributeSet.h"
#include "AbilitySystem/Abilities/Players/RyomaGameplayAbility.h"
#include "RyomaGameplayAbility_Hact.generated.h"

/**
 * 
 */
UCLASS()
class L11_API URyomaGameplayAbility_Hact : public URyomaGameplayAbility
{
	GENERATED_BODY()

public:
	URyomaGameplayAbility_Hact();
	
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr)const override;

	 FGameplayAttribute HactAttribute = UBaseAttributeSet::GetHactCurrentAttribute();
	
	UFUNCTION(BlueprintPure, Category = "AbilitySystem")
	float GetHactCurrentValue() const;

private:
	
	//float HactCurrentValue = 0.0f;

};
