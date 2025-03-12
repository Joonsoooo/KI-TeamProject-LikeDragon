// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "AbilitySystem/BaseAttributeSet.h"
#include "BaseType/BaseStructType.h"
#include "GEExecCalc_DamageTaken.generated.h"

struct FDamageCapture
{
	// 이준수, 캡처에 사용할 속성 선언
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackKatana)
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackGun)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Defense)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)
	DECLARE_ATTRIBUTE_CAPTUREDEF(StaminaTaken)
	DECLARE_ATTRIBUTE_CAPTUREDEF(HactTaken)


	FDamageCapture()
	{
		// 이준수, 선언된 속성에 대한 정의 (속성이 정의된 클래스, 속성 이름, Source : 발동자 / Target : 대상, 스냅샷 여부 
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, AttackKatana, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, AttackGun, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Defense, Target, false);
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, DamageTaken, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, StaminaTaken, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, HactTaken, Source, false);

	}
	
};
/**
 * 
 */
UCLASS()
class L11_API UGEExecCalc_DamageTaken : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UGEExecCalc_DamageTaken();

	// 이준수, 매개변수에는 자동으로 수 많은 값들이 담겨있음, 함수 내부에서 필요한 값들을 재정의
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

public:
	static const FDamageCapture& GetDamageCapture()
	{
		static FDamageCapture DamageCapture;
		return DamageCapture;
	}
};
