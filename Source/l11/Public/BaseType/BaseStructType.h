// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnumType.h"
#include "GameplayTagContainer.h"
#include "ScalableFloat.h"


#include "BaseStructType.generated.h"


class URyomaLinkedAnimLayer;
class UBaseGameplayAbility;
class UInputMappingContext;


USTRUCT(BlueprintType)
struct FRyomaAbilitySet // 이준수, 능력을 활성화하기 위해 능력과, InputTag를 구조체로 묶음
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	//이준수, 부여가능한 능력
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UBaseGameplayAbility> AbilityToGrant;

	bool IsValid() const;
};

USTRUCT(BlueprintType)
struct FRyomaWeaponData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<URyomaLinkedAnimLayer> WeaponAnimLayerToLink;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FRyomaAbilitySet> WeaponAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat WeaponBaseDamage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EWeaponType WeaponType = EWeaponType::None;
};

