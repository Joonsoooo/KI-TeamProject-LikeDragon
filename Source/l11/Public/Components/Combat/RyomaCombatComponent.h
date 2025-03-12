// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Utilities/BaseDebugHelper.h"

#include "RyomaCombatComponent.generated.h"

class ARyomaSwordWeapon;
class AEnemyCharacter;
class ABaseWeapon;
/**
 * 
 */
UCLASS()
class L11_API URyomaCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Combat")
	ARyomaSwordWeapon* GetRyomaCarriedWeaponByTag(FGameplayTag Tag) const;

	// 이준수, 현재 장착하고 있는 무기의 타입을 반환 , 무기를 장착할 때 비교하기 위해 
	UFUNCTION(BlueprintCallable, Category = "Character")
	EWeaponType CurrentEquippedWeaponType();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	ARyomaSwordWeapon*  GetRyomaCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	float GetHeroCurrentEquippedWeaponDamageAtLevel(float Level) const;
	
	// 이준수, PawnCombatComponent에서 정의한 함수 오버라이드 
	virtual void OnHitTargetActor(AActor* HitActor) override;
	virtual void OnWeaponPulledFromTargetActor(AActor* InterectedActor) override;

	//UFUNCTION(Blueprintable)
	virtual void OnTargetHitResult(const FHitResult& HitResult) override;

	FORCEINLINE AEnemyCharacter* GetCurrentTarget() { return CurrentTarget; }
	FORCEINLINE void SetCurrentTarget(AEnemyCharacter* OutCurrentTarget) { CurrentTarget = OutCurrentTarget; }
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	AEnemyCharacter* CurrentTarget;
};


