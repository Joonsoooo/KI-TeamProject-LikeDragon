// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEExecCalc_DamageTaken.h"
#include "GEExecCalc_HactTaken.generated.h"

/**
 * 
 */
UCLASS()
class L11_API UGEExecCalc_HactTaken : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

	UGEExecCalc_HactTaken();

	// 이준수, 매개변수에는 자동으로 수 많은 값들이 담겨있음, 함수 내부에서 필요한 값들을 재정의
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

	static const FDamageCapture& GetDamageCapture()
	{
		static FDamageCapture DamageCapture;
		return DamageCapture;
	}
};
