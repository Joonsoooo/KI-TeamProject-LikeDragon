// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BaseAbilitySystemComponent.h"

#include "AbilitySystem/BaseGamePlayTags.h"
#include "AbilitySystem/Abilities/Players/RyomaGameplayAbility.h"
#include "BaseType/BaseStructType.h"

void UBaseAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	// 이준수 주입한 스펙으로 능력 활성화, (능력을 주입하면 GetActivatableAbilities 함수에 들어가고 Spec로 뽑을 수 있음)
	for (const FGameplayAbilitySpec& Spec : GetActivatableAbilities()) 
	{
		// 이준수, 뽑은 Spec에 InputTag가 있는지 검사, 없으면 건너 뜀
		if (!Spec.DynamicAbilityTags.HasTagExact(InputTag)) continue;

		// 이준수, InputTag가 있으면 능력을 활성화함 
		TryActivateAbility(Spec.Handle);
	}
}

void UBaseAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid() || !InputTag.MatchesTag(BaseGameplayTags::Chara_Ability_Input_Hold))
	{
		return;
	}

	for (const FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (Spec.DynamicAbilityTags.HasTagExact(InputTag) && Spec.IsActive())
		{
			CancelAbilityHandle(Spec.Handle);
		}
	}
}

void UBaseAbilitySystemComponent::GrantRyomaWeaponAbilities(const TArray<FRyomaAbilitySet>& WeaponAbilities,
	int32 Level, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
	if (WeaponAbilities.IsEmpty())
	{
		return;
	}

	for (const FRyomaAbilitySet& WeaponAbilitySet : WeaponAbilities)
	{
		if (!WeaponAbilitySet.IsValid()) continue;

		FGameplayAbilitySpec Spec(WeaponAbilitySet.AbilityToGrant);
		Spec.SourceObject = GetAvatarActor();
		Spec.Level = Level;
		Spec.DynamicAbilityTags.AddTag(WeaponAbilitySet.InputTag);

		
		OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(Spec));
	}
}

void UBaseAbilitySystemComponent::RemoveGrantedRyomaWeaponAbilities(
	TArray<FGameplayAbilitySpecHandle>& SpecHandlesToRemove)
{
	if (SpecHandlesToRemove.IsEmpty())
	{
		return;
	}

	for (FGameplayAbilitySpecHandle& SpecHandle : SpecHandlesToRemove)
	{
		if (SpecHandle.IsValid())
		{
			ClearAbility(SpecHandle);
		}
	}

	SpecHandlesToRemove.Empty();
}

bool UBaseAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag Tag)
{
	// 입력된 Tag가 유효한지 확인
	check(Tag.IsValid())

	// 해당 태그에 일치하는 "활성화 가능한" 어빌리티 목록을 가져옴
	TArray<FGameplayAbilitySpec*> AbilitySpecs;

	GetActivatableGameplayAbilitySpecsByAllMatchingTags(Tag.GetSingleTagContainer(), AbilitySpecs);

	if (!AbilitySpecs.IsEmpty()) 
	{
		// 3 어빌리티 목록 중 하나를 랜덤으로 선택
		const int32 RandomAbilityIndex = FMath::RandRange(0, AbilitySpecs.Num() - 1);
		FGameplayAbilitySpec* AbilitySpec = AbilitySpecs[RandomAbilityIndex];

		check(AbilitySpec); 

		if (!AbilitySpec->IsActive())
		{
			return TryActivateAbility(AbilitySpec->Handle);
		}
	}

	return false;
}
