// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "DataAsset_StartupBase.generated.h"

class UBaseGameplayAbility;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class L11_API UDataAsset_StartupBase : public UDataAsset
{
	GENERATED_BODY()
	
public:
	//김동휘, 부여하는 ASC Level은 단계 1단계 기본부여, (ActivateOnGiveAbilities는 주입되는 즉시 활성화되고, ReactiveAbilities는 주입만 해두고 필요할 때 활성화함)
	virtual void GiveToAbilitySystemComponent(UBaseAbilitySystemComponent* ASC, int32 Level = 1);

protected:
	//김동휘, 부여받은 직후 활성화 되는 주어진 능력들
	UPROPERTY(EditDefaultsOnly, Category = "StartupData")
	TArray<TSubclassOf<UBaseGameplayAbility>> ActivateOnGivenAbilities;

	//김동휘, 특정 조건에 대한 적중반응이나 사망같은 능력들
	UPROPERTY(EditDefaultsOnly, Category = "StartupData")
	TArray<TSubclassOf<UBaseGameplayAbility>> ReactiveAbilities;

	UPROPERTY(EditDefaultsOnly, category = "StartupData")
	TArray<TSubclassOf<UGameplayEffect>> StartupGameplayEffects;
	
	//김동휘, 능력부여, (능력을 부여하기 위해서는 GameplayAbility 클래스, SourceObject, Level이 필요)
	void GrantAbilities(const TArray<TSubclassOf<UBaseGameplayAbility>> GAs, UBaseAbilitySystemComponent* InASC, int32 Level);
};
