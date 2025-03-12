// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/BaseWeapon.h"
#include "BaseType/BaseStructType.h"
#include "GameplayAbilitySpecHandle.h"

#include "RyomaSwordWeapon.generated.h"

/**
 * 
 */
UCLASS()
class L11_API ARyomaSwordWeapon : public ABaseWeapon
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FRyomaWeaponData RyomaWeaponData;

	UFUNCTION(BlueprintCallable)
	void AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& SpecHandles);
	UFUNCTION(BlueprintCallable)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;

private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};
