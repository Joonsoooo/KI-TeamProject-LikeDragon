// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/EnemyGameplayAbility.h"
#include "Characters/Enemies/EnemyCharacter.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "AbilitySystem/BaseGamePlayTags.h"

AEnemyCharacter* UEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedEnemyCharacter.IsValid())
	{
		CachedEnemyCharacter = Cast<AEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedEnemyCharacter.IsValid() ? CachedEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}

FGameplayEffectSpecHandle UEnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> Effect,
	const FScalableFloat& DamageFloat)
{
	check(Effect);

	FGameplayEffectContextHandle ContextHandle;
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle SpecHandle = GetBaseAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		Effect,
		GetAbilityLevel(),
		ContextHandle
	);

	SpecHandle.Data->SetSetByCallerMagnitude(BaseGameplayTags::Shared_SetByCaller_BaseDamage, DamageFloat.GetValueAtLevel(GetAbilityLevel()));

	return SpecHandle;
}
