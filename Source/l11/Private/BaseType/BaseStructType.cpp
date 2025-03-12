// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseType/BaseStructType.h"
#include "AbilitySystem/Abilities/BaseGameplayAbility.h"

bool FRyomaAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant; // 이준수, IsValid 함수는 GameplayAbility에 있음 
}
