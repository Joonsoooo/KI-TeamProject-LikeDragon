// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "BaseAbilitySystemComponent.generated.h"

class ABaseCharacter;
struct FRyomaAbilitySet;
struct FGameplayTag;
/**
 * 
 */
UCLASS()
class L11_API UBaseAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void OnAbilityInputPressed(const FGameplayTag& InputTag);
	void OnAbilityInputReleased(const FGameplayTag& InputTag);

	UFUNCTION(BlueprintCallable, Category = "Ability", meta = (Level = "1"))
	void GrantRyomaWeaponAbilities(const TArray<FRyomaAbilitySet>& WeaponAbilities, int32 Level, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles);
	UFUNCTION(BlueprintCallable, Category = "Ability")
	void RemoveGrantedRyomaWeaponAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& SpecHandlesToRemove);

	UFUNCTION(BlueprintCallable, Category = "Ability")
	bool TryActivateAbilityByTag(FGameplayTag Tag);
};
