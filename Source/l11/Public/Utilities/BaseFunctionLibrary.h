// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BaseFunctionLibrary.generated.h"

class UBaseAbilitySystemComponent;
class UPawnCombatComponent;
/**
 * 
 */
UCLASS()
class L11_API UBaseFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	//김동휘, UBlueprintFunctionLibrary는 내부 접근이므로 public과 static으로 접근해야 함. 액터로 접근해 어빌리티시스템 컴포넌트 가져오기
	static UBaseAbilitySystemComponent* NativeGetAbilitySystemComponentFromActor(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary")
	static void AddPlaygameTagToActor(AActor* Actor, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary")
	static void RemovePlaygameTagFromActor(AActor* Actor, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary")
	static bool NativeActorHasTag(AActor* Actor, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary", meta = (Display = "Does Actor Has Tag", ExpandEnumAsExecs = "OutType"))
	static void BP_HasTag(AActor* Actor, FGameplayTag Tag, EBaseConfirmType& OutType);
	
	static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary", meta = (Display = "Get PawnCombatComponent From Actor", ExpandEnumAsExecs = "OutValidType"))
	static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* Actor, EBaseValidType& OutValidType);

	//김동휘, 피아 식별 헬퍼 함수
	UFUNCTION(BlueprintPure, Category = "FunctionLibrary")
	static bool IsTargetPawnHostile(APawn* OwningPawn, APawn* TargetPawn);

	UFUNCTION(BlueprintPure, Category = "FunctionLibrary")
	static bool IsValidBlock(AActor* Attacker, AActor* Defender);

	//김동휘, GESH 타겟에 적용
	UFUNCTION(BlueprintPure, Category = "FunctionLibrary")
	static bool ApplyGameplayEffectSpecHandleToTargetActor(AActor* Instigator, AActor* TargetActor, const FGameplayEffectSpecHandle& OutSpecHandle);

	// 이준수, Attacker = 공격 액터, HitActor = 맞은 액터, OutAngleDifference = 공격 액터와 맞은 액터의 차이 각도 
	UFUNCTION(BlueprintPure, Category = "FunctionLibrary")
	static FGameplayTag ComputeHitReactDirectionTag(AActor* Attacker, AActor* HitActor, float& OutAngleDifference);
	
	
};
