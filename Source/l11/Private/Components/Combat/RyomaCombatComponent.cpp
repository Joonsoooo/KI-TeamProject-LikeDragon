// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/RyomaCombatComponent.h"
#include "Items/Weapons/RyomaWeapons/RyomaSwordWeapon.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/BaseGamePlayTags.h"
#include "Utilities/BaseFunctionLibrary.h"


ARyomaSwordWeapon* URyomaCombatComponent::GetRyomaCarriedWeaponByTag(FGameplayTag Tag) const
{
	return Cast<ARyomaSwordWeapon>(GetCharacterCarriedWeaponByTag(Tag));
}

EWeaponType URyomaCombatComponent::CurrentEquippedWeaponType()
{

	if (!CurrentEquippedWeaponTag.IsValid())
	{
		return EWeaponType::None;
	}
	
	return Cast<ARyomaSwordWeapon>(GetCharacterCurrentEquippedWeapon())->RyomaWeaponData.WeaponType;
}

ARyomaSwordWeapon* URyomaCombatComponent::GetRyomaCurrentEquippedWeapon() const
{
	return Cast<ARyomaSwordWeapon>(GetCharacterCurrentEquippedWeapon());
}

float URyomaCombatComponent::GetHeroCurrentEquippedWeaponDamageAtLevel(float Level) const
{
	return GetRyomaCurrentEquippedWeapon()->RyomaWeaponData.WeaponBaseDamage.GetValueAtLevel(Level);
}

void URyomaCombatComponent::OnHitTargetActor(AActor* HitActor)
{
    //Debug::Print(GetOwningPawn()->GetActorLabel() + " Hit " + HitActor->GetActorLabel(), FColor::Green);

	UE_LOG(LogTemp, Warning, TEXT("Hit"));
	
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}

	// 이준수, 요소가 없으면 추가 
	OverlappedActors.AddUnique(HitActor);

	//김동휘, 블락 성공시 피격자에게 게임플레이 이벤트 전송(플레이어 -> 몬스터)
	//김동휘, TODO:: Implement Block Check
	bool bIsValidBlock = false;

	const bool bIsEnemyBlocking = UBaseFunctionLibrary::NativeActorHasTag(HitActor, BaseGameplayTags::Shared_Status_Blocking);
	const bool bIsAttackUnblockable = false;

	if (bIsEnemyBlocking && !bIsAttackUnblockable)
	{
		bIsValidBlock = UBaseFunctionLibrary::IsValidBlock(GetOwningPawn(), HitActor);
	}
	
	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;

	if (bIsValidBlock)
	{
		//김동휘, 피격자에게 게임플레이이벤트 전송 GA_Enemy_Block
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor, BaseGameplayTags::Shared_Event_SuccessBlock, Data);
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), BaseGameplayTags::Shared_Event_MeleeHit, Data);
		bool AddTags = UAbilitySystemBlueprintLibrary::AddLooseGameplayTags(GetOwningPawn(), FGameplayTagContainer(FGameplayTag(BaseGameplayTags::Shared_Event_MeleeHit)));
	}
	
	// 이준수, 만약 강공격 어빌리티를 가지고 있다면 강공격 이벤트를 전달 (스테이터스에 강공격 추가)
}

void URyomaCombatComponent::OnWeaponPulledFromTargetActor(AActor* InterectedActor)
{
    //Debug::Print(GetOwningPawn()->GetActorLabel() + "  weapon pulled from " + InterectedActor->GetActorLabel(), FColor::Red);
}

void URyomaCombatComponent::OnTargetHitResult(const FHitResult& HitResult)
{
	Super::OnTargetHitResult(HitResult);

	UE_LOG(LogTemp, Warning, TEXT("Part"));
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