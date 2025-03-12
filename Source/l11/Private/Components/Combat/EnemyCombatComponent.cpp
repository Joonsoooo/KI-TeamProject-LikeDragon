// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/BaseGamePlayTags.h"
#include "Items/Weapons/BaseWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Utilities/BaseDebugHelper.h"
#include "Utilities/BaseFunctionLibrary.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{

	//UE_LOG(LogTemp, Warning, TEXT("Bolc1"));

	if (HitActor)
	{
		//Debug::Print(GetOwningPawn()->GetActorLabel() + TEXT(" is Hitting ") + HitActor->GetActorLabel());
	}

	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}

	OverlappedActors.AddUnique(HitActor);

	//김동휘, TODO:: Implement Block Check
	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking = UBaseFunctionLibrary::NativeActorHasTag(HitActor, BaseGameplayTags::Shared_Status_Blocking);
	const bool bIsAttackUnblockable = false;
	//const bool bIsAttackUnblockable = UBaseFunctionLibrary::NativeActorHasTag(GetOwningPawn(), BaseGameplayTags::Enemy_Status_UnBlockableAttack);

	//UE_LOG(LogTemp, Warning, TEXT("Bolck"));

	
	if (bIsPlayerBlocking && !bIsAttackUnblockable)
	{
		//김동휘, TODO:: Check if the block is valid
		bIsValidBlock = UBaseFunctionLibrary::IsValidBlock(GetOwningPawn(), HitActor);
		//UE_LOG(LogTemp, Warning, TEXT("Player Blocking is valid"));
	}

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;

	if (bIsValidBlock)
	{
		//김동휘, TODO:: Handle Successful Block
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor, BaseGameplayTags::Shared_Event_SuccessBlock, EventData);

	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), BaseGameplayTags::Shared_Event_MeleeHit, EventData);
	}
}

void UEnemyCombatComponent::OnTargetHitResult(const FHitResult& HitResult)
{
	//Super::OnTargetHitResult(HitResult);

	if (UBaseFunctionLibrary::NativeActorHasTag(GetOwningPawn(), BaseGameplayTags::Shared_Event_MeleeHit))
	{
		UE_LOG(LogTemp, Warning, TEXT("Part1"));

		if (HitParticleEffect) // 이미 로드되었는지 확인
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *HitResult.GetActor()->GetName());
			UE_LOG(LogTemp, Warning, TEXT("Impact Point: %s"), *HitResult.ImpactPoint.ToString());
			UE_LOG(LogTemp, Warning, TEXT("Location: %s"), *HitResult.Location.ToString());
			UE_LOG(LogTemp, Warning, TEXT("Blocking Hit: %s"), HitResult.bBlockingHit ? TEXT("True") : TEXT("False"));
	
	 	
			// HitResult를 활용하여 파티클 효과 생성
			UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				HitParticleEffect,            // 사용할 파티클 효과
				HitResult.ImpactPoint,        // 충돌 위치
				FRotationMatrix::MakeFromX(EquipWeapon->GetActorForwardVector()).Rotator() // 무기의 정면 방향
			);

			bool AddTags = UAbilitySystemBlueprintLibrary::RemoveLooseGameplayTags(GetOwningPawn(), FGameplayTagContainer(FGameplayTag(BaseGameplayTags::Shared_Event_MeleeHit)));
		}	
	}
}

