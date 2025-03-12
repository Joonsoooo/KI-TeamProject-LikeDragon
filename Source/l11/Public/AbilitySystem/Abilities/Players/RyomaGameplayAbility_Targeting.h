// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/Players/RyomaGameplayAbility.h"
#include "RyomaGameplayAbility_Targeting.generated.h"

class AEnemyCharacter;
/**
 * 
 */
UCLASS()
class L11_API URyomaGameplayAbility_Targeting : public URyomaGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility);

	
	UFUNCTION(BlueprintCallable)
	void OnTargetingTick(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void SwitchTarget(const TArray<AEnemyCharacter*>& AvailableActors);


public:
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Targeting")
	//AEnemyCharacter* CurrentTarget;
	
private:
	void TryLockOnTarget();
	void GetAvailableActorsToLock();
	
	AEnemyCharacter* GetNearestForwardDirectionFromAvailableActors(const TArray<AEnemyCharacter*>& AvailableActors);
	AEnemyCharacter* FindNearestEnemy(const FVector& Origin, const TArray<AEnemyCharacter*>& ActorsToCheck, float& Distance);

	void CancelTargetingAbility();
	void CleanUp();

	void InitTargetingMovement();
	void ResetTargetingMovement();
	
	UPROPERTY(EditDefaultsOnly, Category = Targeting)
	float TraceDistance = 1000.0f;

	UPROPERTY(EditDefaultsOnly, Category = Targeting)
	FVector TraceBoxSIze = FVector(1000.0f, 1000.0f, 100.0f);

	UPROPERTY(EditDefaultsOnly, Category = Targeting)
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceChannel;

	UPROPERTY(EditDefaultsOnly, Category = Targeting)
	bool bShowDebugShape;

	UPROPERTY(EditDefaultsOnly, Category = Targeting)
	TArray<AEnemyCharacter*> AvailableActorsToLock;

	UPROPERTY(EditDefaultsOnly, Category = Targeting)
	AEnemyCharacter* CurrentTarget;

	UPROPERTY(EditDefaultsOnly, Category="Targeting")
	float TargetingCameraOffset = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category="Targeting")
	float TargetingRotationInterpSpeed = 5.0f;

	UPROPERTY()
	float CachedWalkSpeed = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category="Targeting")
	float TargetingWalkSpeed = 200.0f;

	FRotator CurrentRotation;
};
