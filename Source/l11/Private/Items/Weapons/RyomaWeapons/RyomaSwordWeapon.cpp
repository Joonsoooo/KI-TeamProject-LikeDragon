// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/RyomaWeapons/RyomaSwordWeapon.h"

void ARyomaSwordWeapon::AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& SpecHandles)
{
	GrantedAbilitySpecHandles = SpecHandles;
}

TArray<FGameplayAbilitySpecHandle> ARyomaSwordWeapon::GetGrantedAbilitySpecHandles() const
{
	return GrantedAbilitySpecHandles;
}
