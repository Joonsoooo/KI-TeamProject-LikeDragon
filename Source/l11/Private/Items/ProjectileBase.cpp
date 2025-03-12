// // Fill out your copyright notice in the Description page of Project Settings.
//
//
// #include "Items/ProjectileBase.h"
// #include "NiagaraComponent.h"
// #include "Components/BoxComponent.h"
// #include "GameFramework/ProjectileMovementComponent.h"
// #include "Utilities/BaseFunctionLibrary.h"
// #include "AbilitySystem/BaseGamePlayTags.h"
// #include "Abilities/GameplayAbilityTypes.h"
// #include "AbilitySystemBlueprintLibrary.h"
//
// // Sets default values
// AProjectileBase::AProjectileBase()
// {
//  	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
// 	PrimaryActorTick.bCanEverTick = false;
//
// 	CollisionBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBoxComponent"));
// 	SetRootComponent(CollisionBoxComponent);
// 	CollisionBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
// 	CollisionBoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
// 	CollisionBoxComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
// 	CollisionBoxComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
// 	CollisionBoxComponent->OnComponentHit.AddUniqueDynamic(this, &AProjectileBase::OnProjectileHit);
// 	CollisionBoxComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AProjectileBase::OnProjectileBeginOverlap);
//
// 	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
// 	NiagaraComponent->SetupAttachment(GetRootComponent());
//
// 	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
// 	ProjectileMovementComponent->InitialSpeed = 700.0f;
// 	ProjectileMovementComponent->MaxSpeed = 800.0f;
// 	ProjectileMovementComponent->Velocity = FVector(1.0f, 0.0f, 0.0f);
// 	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
//
// 	//�赿��, ����
// 	InitialLifeSpan = 4.0f;
// }
//
// // Called when the game starts or when spawned
// void AProjectileBase::BeginPlay()
// {
// 	Super::BeginPlay();
//
// 	if (ProjectileDamagePolicy == EProjectileDamagePolicy::OnBeginOverlap)
// 	{
// 		//�赿��, �������ΰ�� ������ Response�� ����
// 		CollisionBoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
// 	}
// }
//
// void AProjectileBase::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
// {
// 	BP_OnSpawnProjectileHitFX(Hit.ImpactPoint);
//
// 	APawn* HitPawn = Cast<APawn>(OtherActor);
//
// 	//�赿��, �ǰݵ� ����� ���ų�, �Ʊ��� ���
// 	if (!HitPawn || !UBaseFunctionLibrary::IsTargetPawnHostile(GetInstigator(), HitPawn))
// 	{
// 		Destroy();
// 		return;
// 	}
//
// 	bool bIsValidBlock = false;
//
// 	//�赿��, �÷��̾ ���������� �Ǻ�
// 	const bool bIsPlayerBlocking = UBaseFunctionLibrary::NativeActorHasTag(HitPawn, BaseGameplayTags::Chara_Status_Blocking);
//
// 	if (bIsPlayerBlocking)
// 	{
// 		//�赿��, ������ ��ȿ���� �ѹ� �� üũ
// 		bIsValidBlock = UBaseFunctionLibrary::IsValidBlock(this, HitPawn);
// 	}
//
// 	//�赿��, GE Data Setting
// 	FGameplayEventData Data;
// 	Data.Instigator = this;
// 	Data.Target = HitPawn;
//
// 	if (bIsValidBlock)
// 	{
// 		//�赿��, Send to HitPawn (SuccessBlock)
// 		// UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
// 		// 	HitPawn,
// 		// 	BaseGameplayTags::Chara_Event_SuccessBlock,
// 		// 	Data
// 		// );
// 	}
// 	else
// 	{
// 		//�赿��, Apply projectile Damage
// 		HandleApplyProjectile(HitPawn, Data);
// 	}
//
// 	Destroy();
// }
//
// void AProjectileBase::OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
// {
// }
//
// // Called every frame
// void AProjectileBase::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);
//
// }
//
// void AProjectileBase::HandleApplyProjectile(APawn* HitPawn, FGameplayEventData& Payload)
// {
// 	checkf(ProjectileDamageSpecHandle.IsValid(), TEXT("ProjectileDamageSpecHandle must be valid"));
// 	const bool bWasApplied = UBaseFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(GetInstigator(), HitPawn, ProjectileDamageSpecHandle);
//
// 	if (bWasApplied)
// 	{
// 		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
// 			HitPawn,
// 			BaseGameplayTags::Shared_Event_HitReact,
// 			Payload
// 		);
// 	}
// }
//
