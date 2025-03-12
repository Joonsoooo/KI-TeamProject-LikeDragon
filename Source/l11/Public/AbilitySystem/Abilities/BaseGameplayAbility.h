// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BaseType/BaseEnumType.h"
#include "BaseGameplayAbility.generated.h"

class UBaseAbilitySystemComponent;
class UPawnCombatComponent;

UENUM(BlueprintType)
enum class EBaseAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven,
};
/**
 * 
 */


UCLASS()
class L11_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	// Joonsoo, AbilitySystemComponent->GiveAbility() is called when called
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	EBaseAbilityActivationPolicy AbilityActivationPolicy = EBaseAbilityActivationPolicy::OnTriggered;

public:
	//CombatComponent 확보
	UFUNCTION(BlueprintPure, Category = "Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "Ability")
	UBaseAbilitySystemComponent* GetBaseAbilitySystemComponentFromActorInfo() const;

	//김동휘, ActiveGameplayEffectHandle 얻기, 이준수, 타겟 액터의 ASC에 정보 주입 
	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& SpecHandle);

    UFUNCTION(BlueprintCallable, Category = "Ability", meta=(Display="Apply Gameplay Effect Spec Handle To Target Actor", ExpandEnumAsExecs = "OutSuccessType"))
    FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& SpecHandle, EBaseSuccessType& OutSuccessType);

	
};
