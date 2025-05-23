// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartupData/DataAsset_StartupBase.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/BaseGameplayAbility.h"

void UDataAsset_StartupBase::GiveToAbilitySystemComponent(UBaseAbilitySystemComponent* ASC, int32 Level)
{
	//김동휘, ASC정보가 유효한지 체크
	check(ASC);

	//김동휘, 두 종류 모두 부여
	GrantAbilities(ActivateOnGivenAbilities, ASC, Level);
	GrantAbilities(ReactiveAbilities, ASC, Level);

	if (!StartupGameplayEffects.IsEmpty())
	{
		for (const TSubclassOf<UGameplayEffect>& BP_Effect : StartupGameplayEffects)
		{
			if (!BP_Effect) continue;

			//김동휘, BP클래스에서 순수 C++클래스를 추출해서 사용
			UGameplayEffect* EffectCDO = BP_Effect->GetDefaultObject<UGameplayEffect>();
			ASC->ApplyGameplayEffectToSelf(EffectCDO, Level, ASC->MakeEffectContext());
		}
	}
}

void UDataAsset_StartupBase::GrantAbilities(const TArray<TSubclassOf<UBaseGameplayAbility>> GAs, UBaseAbilitySystemComponent* InASC, int32 Level)
{
	//김동휘, 게임플레이어빌리티가 없으면 탈출
	if (GAs.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<UBaseGameplayAbility> Ability : GAs)
	{
		//김동휘, 게임플레이 스펙을 만들어서 데이터 주입
		FGameplayAbilitySpec Spec(Ability);
		Spec.SourceObject = InASC->GetAvatarActor();
		Spec.Level = Level;

		//김동휘, 주입된 스펙을 사용할 어빌리티 시스템 컴포넌트에 전달
		InASC->GiveAbility(Spec);
	}
}

