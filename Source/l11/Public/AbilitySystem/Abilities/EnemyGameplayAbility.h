// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/BaseGameplayAbility.h"
#include "EnemyGameplayAbility.generated.h"

class AEnemyCharacter;
class UEnemyCombatComponent;
/**
 * 
 */
UCLASS()
class L11_API UEnemyGameplayAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Ability")
	AEnemyCharacter* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Ability")
	FGameplayEffectSpecHandle MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> Effect, const FScalableFloat& DamageFloat);

private:
	TWeakObjectPtr<AEnemyCharacter> CachedEnemyCharacter;
};
