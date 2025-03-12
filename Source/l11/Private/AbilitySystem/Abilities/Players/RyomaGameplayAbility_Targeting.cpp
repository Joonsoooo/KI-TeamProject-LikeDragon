// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Players/RyomaGameplayAbility_Targeting.h"

#include "AbilitySystem/BaseGamePlayTags.h"
#include "Characters/Players/RyomaCharacter.h"
#include "Components/Combat/RyomaCombatComponent.h"
#include "Controllers/Players/RyomaController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Utilities/BaseDebugHelper.h"
#include "Utilities/BaseFunctionLibrary.h"

void URyomaGameplayAbility_Targeting::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                      const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                      const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	//UE_LOG(LogTemp, Warning, TEXT("Active Ability"));
	
	//타겟팅 활성화 시
	TryLockOnTarget();

	InitTargetingMovement();

	CurrentRotation = GetRyomaCharacterFromActorInfo()->GetActorRotation();
}

void URyomaGameplayAbility_Targeting::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	ResetTargetingMovement();
	
	CleanUp();

	//UE_LOG(LogTemp, Warning, TEXT("End"));

	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void URyomaGameplayAbility_Targeting::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	//UE_LOG(LogTemp, Warning, TEXT("CancelAbility"));
	ResetTargetingMovement();
	
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void URyomaGameplayAbility_Targeting::OnTargetingTick(float DeltaTime)
{
	//타겟팅 유효성
	// if (!CurrentTarget || UBaseFunctionLibrary::NativeActorHasTag(CurrentTarget, BaseGameplayTags::Shared_Status_Dead)
	// 	|| UBaseFunctionLibrary::NativeActorHasTag(GetRyomaCharacterFromActorInfo(), BaseGameplayTags::Shared_Status_Dead)
	// 	)
	if (UBaseFunctionLibrary::NativeActorHasTag(GetRyomaCharacterFromActorInfo(), BaseGameplayTags::Shared_Status_Dead))
	{
		CancelTargetingAbility();
		return;
	}
	
	//플레이어 캐릭터가 타겟팅의 회전이 필요할때
	const bool bShouldOverrideRotation = !UBaseFunctionLibrary::NativeActorHasTag(GetRyomaCharacterFromActorInfo(), BaseGameplayTags::Chara_Status_Swaying)&&
		!UBaseFunctionLibrary::NativeActorHasTag(GetRyomaCharacterFromActorInfo(), BaseGameplayTags::Chara_Ability_Attack_Block);

	GetNearestForwardDirectionFromAvailableActors(AvailableActorsToLock);
	
	// 이준수, 플레이어 캐릭터가 타겟을 바라봄 
	if (bShouldOverrideRotation)
	{
		if (CurrentTarget)
		{
			FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(GetRyomaCharacterFromActorInfo()->GetActorLocation(),
			CurrentTarget->GetActorLocation());

			LookAtRot -= FRotator(TargetingCameraOffset, 0, 0);

			const FRotator CurrentControlRot = GetRyomaControllerFromActorInfo()->GetControlRotation();
			const FRotator TargetRot = FMath::RInterpTo(CurrentControlRot, LookAtRot, DeltaTime, TargetingRotationInterpSpeed);

			//GetRyomaControllerFromActorInfo()->SetControlRotation(FRotator(TargetRot.Pitch, TargetRot.Yaw, 0.f));
			GetRyomaCharacterFromActorInfo()->SetActorRotation(FRotator(0.0f, LookAtRot.Yaw, 0.f));
		}
		else
		{
			CurrentRotation.Pitch = 0.0f;
			CurrentRotation.Roll = 0.0f;

			GetRyomaCharacterFromActorInfo()->SetActorRotation(CurrentRotation);
		}
	}
}

void URyomaGameplayAbility_Targeting::SwitchTarget(const TArray<AEnemyCharacter*>& AvailableActors)
{
	
}

void URyomaGameplayAbility_Targeting::TryLockOnTarget()
{
	//이준수, 타겟팅 가능한 액터 찾기
	GetAvailableActorsToLock();

	//이준수, 타겟팅 가능한 액터가 없으면
	if (AvailableActorsToLock.IsEmpty())
	{
		// CancelTargetingAbility();
		// return;
	}

	CurrentTarget = GetNearestForwardDirectionFromAvailableActors(AvailableActorsToLock);
	GetRyomaCombatComponentFromActorInfo()->SetCurrentTarget(CurrentTarget);
	
	if (CurrentTarget)
	{
		//Debug::Print(CurrentTarget->GetActorNameOrLabel());
	}
	// else
	// {	
	// 	CancelTargetingAbility();
	// }
}

void URyomaGameplayAbility_Targeting::GetAvailableActorsToLock()
{
	TArray<FHitResult> HitResults;

	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetRyomaCharacterFromActorInfo(),
		GetRyomaCharacterFromActorInfo()->GetActorLocation(),
		GetRyomaCharacterFromActorInfo()->GetActorLocation() + GetRyomaCharacterFromActorInfo()->GetActorForwardVector() *TraceDistance,
		TraceBoxSIze / 2.0f,
		GetRyomaCharacterFromActorInfo()->GetActorForwardVector().ToOrientationRotator(),
		TraceChannel,
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::None,
		HitResults,
		true
		);

	for (const FHitResult& HitResult : HitResults)
	{
		if (AActor* HitActor = HitResult.GetActor())
		{
			if (HitActor != GetRyomaCharacterFromActorInfo())
			{
				if (AEnemyCharacter* HitEnemy = Cast<AEnemyCharacter>(HitActor))
				{
					AvailableActorsToLock.AddUnique(HitEnemy);
					
					//Debug::Print(HitActor->GetActorNameOrLabel());
				}
			}
		}
	}
}

AEnemyCharacter* URyomaGameplayAbility_Targeting::GetNearestForwardDirectionFromAvailableActors(
	const TArray<AEnemyCharacter*>& AvailableActors)
{
	TArray<AEnemyCharacter*> ForwardEnemys;
	
	// 일단 직선 범위의 적들을 또 뽑아
	for ( AEnemyCharacter* Enemy: AvailableActors)
	{
		const FVector CharacterForward = GetRyomaCharacterFromActorInfo()->GetActorForwardVector();
		const FVector ToEnemyNormalized = (Enemy->GetActorLocation() - GetRyomaCharacterFromActorInfo()->GetActorLocation()).GetSafeNormal();

		//이준수, 내적을 통해 각도 값 구하기
		const float DotResult = FVector::DotProduct(CharacterForward, ToEnemyNormalized);
		float OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);

		if (OutAngleDifference >= -20.f && OutAngleDifference <= 20.f)
		{
			ForwardEnemys.AddUnique(Enemy);
		}
	}
	// 거기서 가장 가까운 얘를 뽑아
	float Distance = 0.f;
	return FindNearestEnemy(GetRyomaCharacterFromActorInfo()->GetActorLocation(), ForwardEnemys, Distance);
}

AEnemyCharacter* URyomaGameplayAbility_Targeting::FindNearestEnemy(const FVector& Origin,
	const TArray<AEnemyCharacter*>& ActorsToCheck, float& Distance)
{
	AEnemyCharacter* NearestActor = nullptr;
	float DistanceFromNearestActor = Distance = TNumericLimits<float>::Max();

	for (AEnemyCharacter* ActorToCheck : ActorsToCheck)
	{
		if (ActorToCheck)
		{
			const float DistanceFromActorToCheck = (Origin - ActorToCheck->GetActorLocation()).SizeSquared();
			if (DistanceFromActorToCheck < DistanceFromNearestActor)
			{
				NearestActor = ActorToCheck;
				DistanceFromNearestActor = DistanceFromActorToCheck;
			}
		}
	}

	if (NearestActor)
	{
		Distance = FMath::Sqrt(DistanceFromNearestActor);
	}

	return NearestActor;
}

void URyomaGameplayAbility_Targeting::CancelTargetingAbility()
{
	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);

	ResetTargetingMovement();

	CleanUp();
	UE_LOG(LogTemp, Warning, TEXT("Cancel"));

}

void URyomaGameplayAbility_Targeting::CleanUp()
{
	AvailableActorsToLock.Empty();
	//CurrentTarget = nullptr;
	CachedWalkSpeed = 0.0f;
}

void URyomaGameplayAbility_Targeting::InitTargetingMovement()
{
	//CachedWalkSpeed = GetRyomaCharacterFromActorInfo()->GetCharacterMovement()->GetMaxSpeed();
	//UE_LOG(LogTemp, Warning, TEXT("%f"), CachedWalkSpeed);

	UE_LOG(LogTemp, Warning, TEXT("InitTargetingMovement"));
	GetRyomaCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = TargetingWalkSpeed;
}

void URyomaGameplayAbility_Targeting::ResetTargetingMovement()
{
	UE_LOG(LogTemp, Warning, TEXT("Reset"));
	GetRyomaCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = 400.0f;

	
	// if (FMath::IsNearlyEqual(CachedWalkSpeed, TargetingWalkSpeed, 0.1f))
	// {
	// 	GetRyomaCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	// }
	// else if (CachedWalkSpeed > 0.0f)
	// {
	// 	GetRyomaCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = CachedWalkSpeed;
	// }

	// UE_LOG(LogTemp, Warning, TEXT("Reset"));
	// if (FMath::IsNearlyEqual(CachedWalkSpeed, TargetingWalkSpeed, 0.1f))
	// {
	// 	GetRyomaCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	// }
}
