// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/PawnUIComponent.h"
#include "RyomaUIComponent.generated.h"

/**
 * 
 */
UCLASS()
class L11_API URyomaUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangeDelegate OnStaminaCurrentChanged;

	UPROPERTY(BlueprintAssignable)
	FOnPercentChangeDelegate OnHactCurrentChanged;
	
};
