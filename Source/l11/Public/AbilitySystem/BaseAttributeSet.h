// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"

#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "BaseAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

class ARyomaCharacter;
class IPawnUIInterface;
/**
 * 
 */
UCLASS()
class L11_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UBaseAttributeSet();

	//이준수, GameplayEffect에 의해 스탯 값이 바뀌면 자동으로 호출됨 
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	//김동휘, 체력 현재
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData HealthCurrent;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, HealthCurrent)

	//김동휘, 체력 최대
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData HealthMax;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, HealthMax)

	//김동휘, 투기 현재
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData StaminaCurrent;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, StaminaCurrent)

	//김동휘, 투기 최대
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData StaminaMax;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, StaminaMax)

	//이준수, 투기 개수
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData HactCurrent;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, HactCurrent)

	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData HactMax;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, HactMax)

	
	//김동휘, 공격력 일도
	UPROPERTY(BlueprintReadOnly, Category="Damage")
	FGameplayAttributeData AttackKatana;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, AttackKatana)

	//김동휘, 공격력 권총
	UPROPERTY(BlueprintReadOnly, Category="Damage")
	FGameplayAttributeData AttackGun;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, AttackGun)

	//김동휘, 치명타 확률
	UPROPERTY(BlueprintReadOnly, Category="Damage")
	FGameplayAttributeData CriticalChance;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, CriticalChance)

	//김동휘, 치명타 배율
	UPROPERTY(BlueprintReadOnly, Category="Damage")
	FGameplayAttributeData CriticalMultiplier;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, CriticalMultiplier)

	//김동휘, 방어력
	UPROPERTY(BlueprintReadOnly, Category="Damage")
	FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Defense)

	// 이준수, 데미지 전달 값
	UPROPERTY(BlueprintReadOnly, Category="Damage")
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, DamageTaken)

	UPROPERTY(BlueprintReadOnly, Category="Damage")
	FGameplayAttributeData StaminaTaken;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, StaminaTaken)

	UPROPERTY(BlueprintReadOnly, Category="Damage")
	FGameplayAttributeData HactTaken;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, HactTaken)

private:       
	TWeakInterfacePtr<IPawnUIInterface> CachedUIInterface;
	TWeakObjectPtr<ARyomaCharacter> CachedRyomaCharacter;
};
