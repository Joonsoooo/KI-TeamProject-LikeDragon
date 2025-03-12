// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExecCalc/UGEExecCalc_StaminaRecovery.h"
//#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"

#include "AbilitySystem/BaseAttributeSet.h"
#include "AbilitySystem/BaseGamePlayTags.h"
#include "Utilities/BaseDebugHelper.h"

// struct FDamageCapture
// {
// 	// 이준수, 캡처에 사용할 속성 선언
// 	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackKatana)
// 	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackGun)
// 	DECLARE_ATTRIBUTE_CAPTUREDEF(Defense)
// 	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)
// 	DECLARE_ATTRIBUTE_CAPTUREDEF(StaminaTaken)
//
//
// 	FDamageCapture()
// 	{
// 		// 이준수, 선언된 속성에 대한 정의 (속성이 정의된 클래스, 속성 이름, Source : 발동자 / Target : 대상, 스냅샷 여부 
// 		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, AttackKatana, Source, false);
// 		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, AttackGun, Source, false);
// 		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Defense, Target, false);
// 		
// 		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, DamageTaken, Target, false);
// 		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, StaminaTaken, Source, false);
//
// 	}
// 	
// };
//
// static const FDamageCapture& GetDamageCapture()
// {
// 	static FDamageCapture DamageCapture;
// 	return DamageCapture;
// }

// static const FDamageCapture& GetDamageCapture()
// {
// 	static FDamageCapture DamageCapture;
// 	return DamageCapture;
// }

UUGEExecCalc_StaminaRecovery::UUGEExecCalc_StaminaRecovery()
{
	RelevantAttributesToCapture.Add(GetDamageCapture().AttackKatanaDef);
	RelevantAttributesToCapture.Add(GetDamageCapture().AttackGunDef);
	RelevantAttributesToCapture.Add(GetDamageCapture().DefenseDef);
	RelevantAttributesToCapture.Add(GetDamageCapture().DamageTakenDef);
	RelevantAttributesToCapture.Add(GetDamageCapture().StaminaTakenDef);
}

void UUGEExecCalc_StaminaRecovery::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	//Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	//UE_LOG(LogTemp, Warning, TEXT("Execute_Implementation"));
	
	// 이준수, 매개변수에 있는 스펙들 변수에 담음 
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	// 이준수, 속성 값을 계산할 때 사용하는 구조체 
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttack = 0.0;
	// 이준수, EvaluateParameters에 있는 AttackKatanaDef 값을 SourceAttack 여기에 담음 
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().AttackKatanaDef, EvaluateParameters, SourceAttack);

	float BaseDamage = .0f;
	int32 CachedComboCount_Light = 0;
	int32 CachedComboCount_Heavy = 0;

	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		// TagMagnitude의 키에 Shared_SetByCaller_BaseDamage 가 있으면 값을 가져옴 
		if (TagMagnitude.Key.MatchesTagExact((BaseGameplayTags::Shared_SetByCaller_BaseDamage)))
		{
			BaseDamage = TagMagnitude.Value;
			//Debug::Print(TEXT("BaseDamage"), BaseDamage);
		}

		if (TagMagnitude.Key.MatchesTagExact(BaseGameplayTags::Shared_SetByCaller_AttackType_Light))
		{
			CachedComboCount_Light = TagMagnitude.Value;
			//Debug::Print(TEXT("CachedComboCount_Light"), CachedComboCount_Light);
		}

		if (TagMagnitude.Key.MatchesTagExact(BaseGameplayTags::Shared_SetByCaller_AttackType_Heavy))
		{
			CachedComboCount_Heavy = TagMagnitude.Value;
			//Debug::Print(TEXT("CachedComboCount_Heavy"), CachedComboCount_Heavy);
		}
		
	}

	
	float TargetDefence = 0.f;
	// Defence 값을 가져옴 
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().DefenseDef, EvaluateParameters, TargetDefence);
	//Debug::Print(TEXT("TargetDefence"), TargetDefence);

	// 이준수, 콤보 값에 따라 추가 데미지 적용 
	if (CachedComboCount_Light !=0)
	{
		const float LightDamageIncrePercent = (CachedComboCount_Light - 1) * 0.05 + 1.0f;
		BaseDamage *= LightDamageIncrePercent;
		//Debug::Print(TEXT("CachedComboCount_Light BaseDamage"), BaseDamage);
	}

	if (CachedComboCount_Heavy != 0)
	{
		const float HeavyDamageIncrePercent = CachedComboCount_Heavy * 0.15f + 1.f;
		BaseDamage *= HeavyDamageIncrePercent;
		//Debug::Print(TEXT("CachedComboCount_Heavy BaseDamage"), BaseDamage);
	}

	// 최종 공격 값 계산 
	const float FinalDamage = (BaseDamage * SourceAttack / TargetDefence) * 3.0f;
	//Debug::Print(TEXT("FFFFinalDamage"), FinalDamage);
	
	if (FinalDamage > 0.f)
	{
		//UE_LOG(LogTemp, Warning, TEXT("FFFFFFFFFFFFFFinalDamage"));
		
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetDamageCapture().StaminaTakenProperty, // 스테미나 회복되게 
				EGameplayModOp::Override,
				FinalDamage
			)
		);

		
		// // 이준수, 최종 값인 FinalDamage를 DamageTakenProperty 속성에 덮어 씌움, 0보다 작으면 그럼 일반 DamageTakenProperty 값으로 
		// OutExecutionOutput.AddOutputModifier(
		// 	FGameplayModifierEvaluatedData(
		// 		GetDamageCapture().DamageTakenProperty, // 데미지 값을 AttributeSet에 전달하고 테이큰의 값이 바뀐걸 알게 되면 체력을 깎고 체력이 깎인 것을 알게 되면 체력을 수정 
		// 		EGameplayModOp::Override,
		// 		FinalDamage
		// 	)
		// );

	}
}
