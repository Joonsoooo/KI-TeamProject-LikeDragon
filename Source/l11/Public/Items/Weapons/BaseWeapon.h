// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class UBoxComponent;

DECLARE_DELEGATE_OneParam(FOnTargetInteractedDelegate, AActor*)
DECLARE_DELEGATE_OneParam(FOnTargetHitResultDelegate, const FHitResult&);

UCLASS()
class L11_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

	// 이준수, 때렸을 때 델리게이트
	FOnTargetInteractedDelegate OnWeaponHitTarget;
	// 이준수, 때리는거 끝났을 때 델리게이트 
	FOnTargetInteractedDelegate OnWeaponPulledFromTarget;
	FOnTargetHitResultDelegate OnTargetHitResult;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	UBoxComponent* WeaponCollisionBox;

	
	UFUNCTION()
	virtual void OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	virtual void OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnCollisionBoxHitLinetrace(AActor* OtherActor);
public:
	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const {return WeaponCollisionBox;}
};
