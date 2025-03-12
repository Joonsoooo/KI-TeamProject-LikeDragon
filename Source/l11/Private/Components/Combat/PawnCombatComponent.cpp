// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PawnCombatComponent.h"
#include "Items/Weapons/BaseWeapon.h"
#include "Components/BoxComponent.h"
#include "Utilities/BaseDebugHelper.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag WeaponTag, ABaseWeapon* Weapon,
                                                 bool bRegisterAsEquippedWeapon)
{
	checkf(!CharacterCarriedWeaponMap.Contains(WeaponTag), TEXT("%s has already been as carried weapon"), *WeaponTag.ToString());
	check(Weapon);

	CharacterCarriedWeaponMap.Emplace(WeaponTag, Weapon);

	// 이준수, 무기를 등록할 때 BaseWeapon에 있는 델리게이트와 바인딩
	EquipWeapon = Weapon;
	Weapon->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
	Weapon->OnWeaponPulledFromTarget.BindUObject(this, &ThisClass::OnWeaponPulledFromTargetActor);
	Weapon->OnTargetHitResult.BindUObject(this, &ThisClass::OnTargetHitResult);

	// 이준수, 장착한 무기로 등록이 되면 현재 장착무기를 변경
	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = WeaponTag;
	}
}

ABaseWeapon* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag WeaponTag) const
{
	//Map 컨테이너에 WeaponTag의 데이터가 있으면 AWeaponBase를 반환
	if (CharacterCarriedWeaponMap.Contains(WeaponTag))
	{
		if (ABaseWeapon* const* FoundWeapon = CharacterCarriedWeaponMap.Find(WeaponTag))
		{
			return *FoundWeapon;
		}
	}

	return nullptr;
}

ABaseWeapon* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}

	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}

bool UPawnCombatComponent::IsEquippedWeapon(FGameplayTag WeaponTag)
{
	return WeaponTag == CurrentEquippedWeaponTag ? true : false;
}

void UPawnCombatComponent::ToggleWeaponCollision(bool bUse, EToggleDamageType ToggleDamageType)
{
	if (ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon)
	{
		ABaseWeapon* Weapon = GetCharacterCurrentEquippedWeapon();

		check(Weapon);

		if (bUse)
		{
			Weapon->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			//Debug::Print(Weapon->GetName() + TEXT(" Collision enabled"), FColor::Green);
		}
		else
		{
			Weapon->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			//Debug::Print(Weapon->GetName() + TEXT(" Collision disabled"), FColor::Red);

			// 이준수, 공격 모션이 끝나면 배열을 초기화 
			OverlappedActors.Empty();
		}
	}
}

void UPawnCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	//김동휘, 자식에서 구현
}

void UPawnCombatComponent::OnWeaponPulledFromTargetActor(AActor* InterectedActor)
{
	//김동휘, 자식에서 구현
}



