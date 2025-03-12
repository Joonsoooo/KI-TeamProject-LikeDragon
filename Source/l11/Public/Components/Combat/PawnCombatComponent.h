// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/PawnExtensionComponent.h"
#include "BaseType/BaseEnumType.h"

#include "PawnCombatComponent.generated.h"

class ABaseWeapon;
class UNiagaraSystem;

UENUM()
enum class EToggleDamageType : uint8
{
	CurrentEquippedWeapon,
	LeftHand,
	RightHand,
};

/**
 * 
 */
UCLASS()
class L11_API UPawnCombatComponent : public UPawnExtensionComponent
{
	GENERATED_BODY()

public:
	//이준수 생성된 무기 등록, (블루프린트에서 무기를 스폰할 때 등록함)
	UFUNCTION(BlueprintCallable, Category = "Character")
	void RegisterSpawnedWeapon(FGameplayTag WeaponTag, ABaseWeapon* Weapon, bool bRegisterAsEquippedWeapon = false);

	//이준수 캐릭터가 휴대하는 무기, (RegisterSpawnedWeapon에서 CharacterCarriedWeaponMap 변수에 Tag와 BaseWeapon을 넣는데 거기에 있는 Tag 값으로 무기를 반환)
	UFUNCTION(BlueprintCallable, Category = "Character")
	ABaseWeapon* GetCharacterCarriedWeaponByTag(FGameplayTag WeaponTag) const;

	//이준수, 캐릭터가 장착한 무기, (CurrenEquippedWeaponTag 변수를 통해 Weapon을 찾음)
	UFUNCTION(BlueprintCallable, Category = "Character")
	ABaseWeapon* GetCharacterCurrentEquippedWeapon() const;

	// 이준수, 현재 장착하고 있는 무기를 태그를 이용해서 비교 똑같으면 true, 다르면 false
	UFUNCTION(BlueprintCallable, Category = "Character")
	bool IsEquippedWeapon(FGameplayTag WeaponTag);
	
	//이준수, 캐릭터가 소유한 무기의 태그, (블루프린트에서 RegisterSpawnedWeapon를 할 때 bRegisterAsEquippedWeapon 변수를 체크하면 WeaponTag가 변수에 담김)
	UPROPERTY(BlueprintReadWrite, Category = "Character")
	FGameplayTag CurrentEquippedWeaponTag;

	UFUNCTION(blueprintcallable, Category = "Combat")
	void ToggleWeaponCollision(bool bUse, EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon);
	
	//김동휘, HitDetection
	virtual void OnHitTargetActor(AActor* HitActor);
	virtual void OnWeaponPulledFromTargetActor(AActor* InterectedActor);
	virtual void OnTargetHitResult(const FHitResult& HitResult);

protected:
	// 이준수, 오버랩된 액터들 
	TArray<AActor*> OverlappedActors;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UParticleSystem* HitParticleEffect;

	UPROPERTY()
	ABaseWeapon* EquipWeapon;
private:
	//이준수, 캐릭터는 여러 무기를 소유할 수 있다
	TMap<FGameplayTag, ABaseWeapon*> CharacterCarriedWeaponMap;
};

inline void UPawnCombatComponent::OnTargetHitResult(const FHitResult& HitResult)
{
}

