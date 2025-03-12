// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Players/RyomaGameplayAbility.h"

#include "Characters/Players/RyomaCharacter.h"
#include "Controllers/Players/RyomaController.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "AbilitySystem/BaseGamePlayTags.h"
#include "AbilitySystem/Abilities/Players/RyomaGameplayAbility_Targeting.h"
#include "Kismet/KismetMathLibrary.h"

void URyomaGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// // 부모 클래스 포인터
	// URyomaGameplayAbility* BaseAbility = this;
	//
	// // 자식 클래스 포인터로 캐스팅 시도
	// TargetingAbility = Cast<URyomaGameplayAbility_Targeting>(BaseAbility);
	//
	// if (TargetingAbility)
	// {
	// 	// 캐스팅 성공: TargetingAbility는 자식 클래스의 객체
	// 	// TargetingAbility->SomeTargetingFunction();
	// 	UE_LOG(LogTemp, Log, TEXT("Successfully casted to URyomaGameplayAbility_Targeting."));
	// }
	// else
	// {
	// 	// 캐스팅 실패: BaseAbility는 자식 클래스 타입이 아님
	// 	UE_LOG(LogTemp, Warning, TEXT("Failed to cast to URyomaGameplayAbility_Targeting."));
	// }
	
	// TargetingAbility = Cast<URyomaGameplayAbility_Targeting>(this);
	//
	// // 캐스팅 성공 여부 확인
	// if (TargetingAbility)
	// {
	// 	// 성공한 경우
	// 	UE_LOG(LogTemp, Log, TEXT("Successfully cast to URyomaGameplayAbility_Targeting!"));
	// 	
	// }
	// else
	// {
	// 	// 실패한 경우
	// 	UE_LOG(LogTemp, Warning, TEXT("Cast to URyomaGameplayAbility_Targeting failed!"));
	// }

}

ARyomaCharacter* URyomaGameplayAbility::GetRyomaCharacterFromActorInfo()
{
	if (!CachedRyomaCharacter.IsValid())
	{
		CachedRyomaCharacter = Cast<ARyomaCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedRyomaCharacter.IsValid() ? CachedRyomaCharacter.Get() : nullptr;
}

ARyomaController* URyomaGameplayAbility::GetRyomaControllerFromActorInfo()
{
	if (!CachedRyomaController.IsValid())
	{
		CachedRyomaController = Cast<ARyomaController>(CurrentActorInfo->PlayerController);

	}
	
	return CachedRyomaController.IsValid() ? CachedRyomaController.Get() : nullptr;
}

URyomaCombatComponent* URyomaGameplayAbility::GetRyomaCombatComponentFromActorInfo()
{
	return GetRyomaCharacterFromActorInfo()->GetRyomaCombatComponent();
}

FGameplayEffectSpecHandle URyomaGameplayAbility::MakerRyomaDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> Effect,
	float WeaponBaseDamage, FGameplayTag AttackTypeTag, int32 ComboCount)
{

	check(Effect);

	//이준수 ContextHandle을 만들어서 타겟 정보 주입
	FGameplayEffectContextHandle ContextHandle;
	ContextHandle.SetAbility(this); // 이준수, 핸들에 어빌리티 담음 
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo()); // 이준수, 능력을 발생시킨 아이템 
    ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo()); // 이준수, 능력을 발생시킨 사람

	// 이준수, SpecHandle을 만들어 ContextHandle 정보 주입
	FGameplayEffectSpecHandle SpecHandle = GetBaseAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(Effect, GetAbilityLevel(), ContextHandle);

	// 이준수, 태그가 없으면 일단 기본 값 전달 
	SpecHandle.Data->SetSetByCallerMagnitude(
		BaseGameplayTags::Shared_SetByCaller_BaseDamage,
		WeaponBaseDamage
		);

	// 이준수, 태그가 있으면 태그와 콤보카운트를 묶어 전달
	if (AttackTypeTag.IsValid())
	{
		//UE_LOG(LogTemp, Warning, TEXT("Call"));
		SpecHandle.Data->SetSetByCallerMagnitude(AttackTypeTag, ComboCount);
	}

	return SpecHandle;
}

FVector URyomaGameplayAbility::SetMoveAroundTargetDistance(FVector SwayDirection, AEnemyCharacter* Enemy, float MoveDistance)
{
	// 방어 코드: Enemy가 nullptr인지 확인
	if (!Enemy)
	{
		return FVector::ZeroVector;
	}

	// 이동을 위한 변수 선언
	FVector CenterLocation = Enemy->GetActorLocation(); // 원의 중심 위치 (적의 위치)
	FVector StartLocation = GetRyomaCharacterFromActorInfo()->GetActorLocation(); // 시작 위치 (플레이어 위치)
	float Radius = FVector::Dist(StartLocation, CenterLocation);

	FVector FinalTargetLocation; // 최종 목표 위치

	// 현재 위치에서 중심으로의 방향 벡터
	FVector DirectionToCenter = (StartLocation - CenterLocation).GetSafeNormal();
	float CurrentAngle = FMath::Atan2(DirectionToCenter.Y, DirectionToCenter.X);

	// 입력 벡터와 중심 벡터 간 크로스 프로덕트 계산
	float CrossZ = FVector::CrossProduct(DirectionToCenter, SwayDirection).Z;
	float MovementDirectionSign = (CrossZ > 0.0f) ? 1.0f : -1.0f; // A: 반시계(+), D: 시계(-)

	// 목표 각도 계산
	float TargetAngle = CurrentAngle + MovementDirectionSign * (MoveDistance / Radius);

	// 최종 목표 위치 계산
	FinalTargetLocation.X = CenterLocation.X + Radius * FMath::Cos(TargetAngle);
	FinalTargetLocation.Y = CenterLocation.Y + Radius * FMath::Sin(TargetAngle);
	FinalTargetLocation.Z = StartLocation.Z;

	FVector TargetLocation = FinalTargetLocation;

	// 디버그 스피어 그리기 (TargetLocation에 디버그 표시)
	DrawDebugSphere(
		GetWorld(),             // 현재 월드
		TargetLocation,         // 스피어 중심 위치
		50.0f,                  // 스피어 반지름
		12,                     // 스피어 분할(폴리곤 수)
		FColor::Green,          // 스피어 색상
		false,                  // 영구 여부 (false면 일정 시간 후 사라짐)
		5.0f                    // 지속 시간 (5초)
	);

	return TargetLocation;
}


void URyomaGameplayAbility::MoveAroundTargetTick(FVector TargetLocation, AEnemyCharacter* Enemy, float DeltaTime)
{
	FVector SmoothLocation = FMath::VInterpTo(GetRyomaCharacterFromActorInfo()->GetActorLocation(), TargetLocation, DeltaTime, 1.0f);
	GetRyomaCharacterFromActorInfo()->SetActorLocation(SmoothLocation);
	FRotator TargetRotation = Enemy->GetActorRotation();
	//FRotator SmoothRotation = FMath::RInterpTo(GetRyomaCharacterFromActorInfo()->GetActorRotation(), TargetRotation, DeltaTime, 5.0f);
	//GetRyomaCharacterFromActorInfo()->SetActorRotation(TargetRotation);
	GetRyomaCharacterFromActorInfo()->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetRyomaCharacterFromActorInfo()->GetActorLocation(), Enemy->GetActorLocation()));
}




