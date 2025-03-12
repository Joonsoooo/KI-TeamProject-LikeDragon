// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponent.h"
#include "PawnUIComponent.generated.h"

// UI 스탯 변화를 알려줄 델리게이트 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPercentChangeDelegate, float, NewPercent);

/**
 * 
 */
UCLASS()
class L11_API UPawnUIComponent : public UPawnExtensionComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangeDelegate OnHealthCurrentChanged;

	UPROPERTY(BlueprintAssignable)
	FOnPercentChangeDelegate OnDamageCurrentChanged;
};
