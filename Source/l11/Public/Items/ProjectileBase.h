// // Fill out your copyright notice in the Description page of Project Settings.
//
// #pragma once
//
// #include "CoreMinimal.h"
// #include "GameFramework/Actor.h"
// #include "GameplayEffectTypes.h"
// #include "ProjectileBase.generated.h"
//
// struct FGameplayEventData;
// class UProjectileMovementComponent;
// class UBoxComponent;
// class UNiagaraComponent;
//
// UENUM()
// enum class EProjectileDamagePolicy
// {
// 	OnHit,
// 	OnBeginOverlap,
// };
//
// UCLASS()
// class L11_API AProjectileBase : public AActor
// {
// 	GENERATED_BODY()
// 	
// public:	
// 	// Sets default values for this actor's properties
// 	AProjectileBase();
//
// protected:
// 	// Called when the game starts or when spawned
// 	virtual void BeginPlay() override;
//
// private:
// 	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Projectile")
// 	UBoxComponent* CollisionBoxComponent;
//
// 	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Projectile")
// 	UNiagaraComponent* NiagaraComponent;
//
// 	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Projectile")
// 	UProjectileMovementComponent* ProjectileMovementComponent;
//
// 	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Projectile")
// 	EProjectileDamagePolicy ProjectileDamagePolicy = EProjectileDamagePolicy::OnHit;
//
// protected:
// 	UFUNCTION()
// 	virtual void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
//
// 	UFUNCTION()
// 	virtual void OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
//
// 	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Spawn Projectile Hit FX"))
// 	void BP_OnSpawnProjectileHitFX(const FVector& HitLocation);
//
// 	//�赿��, ������ ���Ⱑ���ϵ��� ��ũ�ο��� ExposeOnSpawn ���
// 	UPROPERTY(BlueprintReadOnly, Category = "Projectile", meta = (ExposeOnSpawn = true))
// 	FGameplayEffectSpecHandle ProjectileDamageSpecHandle;
//
// public:	
// 	// Called every frame
// 	virtual void Tick(float DeltaTime) override;
//
// private:
// 	void HandleApplyProjectile(APawn* HitPawn, FGameplayEventData& Payload);
// };
