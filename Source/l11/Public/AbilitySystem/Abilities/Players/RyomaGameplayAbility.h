// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/BaseGameplayAbility.h"
#include "RyomaGameplayAbility.generated.h"

class ARyomaCharacter;
class ARyomaController;
class URyomaCombatComponent;
class URyomaGameplayAbility_Targeting;
class AEnemyCharacter;
/**
 * 
 */
UCLASS()
class L11_API URyomaGameplayAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	
public:
	UFUNCTION(BlueprintPure, Category = "Ability")
	ARyomaCharacter* GetRyomaCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Ability")
	ARyomaController* GetRyomaControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Ability")
	URyomaCombatComponent* GetRyomaCombatComponentFromActorInfo();

	// 이준수, 핸들을 만들고 핸들로 스펙을 만들어서 스펙을 전달하는 구조
	// 이준수, 핸들과 스팩을 나눈 이유는 대충 스펙은 무겁고 핸들은 스펙의 참조 역할이라 가벼워 핸들에서 스펙을 정의하고 최종적으로 스펙을 전달한다 생각하자 
	UFUNCTION(BlueprintPure, Category = "Ability")
	FGameplayEffectSpecHandle MakerRyomaDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> Effect, float WeaponBaseDamage, FGameplayTag AttackTypeTag, int32 ComboCount);

	
	UFUNCTION(BlueprintCallable, Category = "Ability")
	FVector SetMoveAroundTargetDistance(FVector SwayDirection, AEnemyCharacter* Enemy, float MoveDistance);
	UFUNCTION(BlueprintCallable, Category = "Ability")
	void MoveAroundTargetTick(FVector TargetLocation, AEnemyCharacter* Enemy, float DeltaTime);
 	
private:
	TWeakObjectPtr<ARyomaCharacter> CachedRyomaCharacter;
	TWeakObjectPtr<ARyomaController> CachedRyomaController;
	

};
