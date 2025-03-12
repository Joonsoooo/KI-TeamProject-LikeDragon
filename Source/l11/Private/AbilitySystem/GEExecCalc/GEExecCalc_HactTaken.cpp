// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExecCalc/GEExecCalc_HactTaken.h"
#include "Utilities/BaseDebugHelper.h"
#include "AbilitySystem/BaseGamePlayTags.h"

UGEExecCalc_HactTaken::UGEExecCalc_HactTaken()
{
	RelevantAttributesToCapture.Add(GetDamageCapture().HactTakenDef);
}

void UGEExecCalc_HactTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();
    
    // 이준수, 속성 값을 계산할 때 사용하는 구조체 
    FAggregatorEvaluateParameters EvaluateParameters;
    EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float HactNumber = 0.0f;
	
	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact((BaseGameplayTags::Shared_SetByCaller_HactCount)))

		{
			HactNumber = TagMagnitude.Value;
			//Debug::Print(TEXT("HactNumber"), HactNumber);
		}
	}

	if (HactNumber > 0.f)
	{
		// 이준수, 최종 값인 FinalDamage를 DamageTakenProperty 속성에 덮어 씌움, 0보다 작으면 그럼 일반 DamageTakenProperty 값으로 
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetDamageCapture().HactTakenProperty, // 데미지 값을 AttributeSet에 전달하고 테이큰의 값이 바뀐걸 알게 되면 체력을 깎고 체력이 깎인 것을 알게 되면 체력을 수정 
				EGameplayModOp::Override,
				HactNumber
			)
		);
	}
	
	//Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);
}
