// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartupData/DataAsset_StartupRyoma.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/BaseGameplayAbility.h"
#include "BaseType/BaseStructType.h"

void UDataAsset_StartupRyoma::GiveToAbilitySystemComponent(UBaseAbilitySystemComponent* ASC, int32 Level)
{
	Super::GiveToAbilitySystemComponent(ASC, Level);

	for (const FRyomaAbilitySet& AbilitySet : RyomaStartupAbilitySets)
	{
		if (!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec Spec(AbilitySet.AbilityToGrant); // 이준수, AbilityToGrant 변수를 Spec으로 만듦
		Spec.SourceObject = ASC->GetAvatarActor();
		Spec.Level = Level;
		// 이준수, 동적 태그 생성
		Spec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

		ASC->GiveAbility(Spec);
	}
}
