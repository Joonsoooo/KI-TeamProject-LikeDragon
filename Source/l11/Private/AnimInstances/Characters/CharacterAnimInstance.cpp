// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Characters/CharacterAnimInstance.h"
#include "Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"


void UCharacterAnimInstance::NativeInitializeAnimation()
{
	//TryGetPawnOwner 소유자의 Pawn 반환
	OwningCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());

	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}

}

void UCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DelatSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}

	// 이준수, 캐릭터의 이동 속도 반환
	GroundSpeed = OwningCharacter->GetVelocity().Size2D();

	// 이준수, 캐릭터가 이동하고 있는지 반환
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;

	// 이준수, 캐릭터가 이동하고 있는 방향 반환 (캐릭터가 이동하는 축과 캐릭터의 월드 Yaw 값을 비교하여 어느 쪽으로 이동하고 있는지 알 수 있음) 
	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());

	//UE_LOG(LogTemp, Warning, TEXT("%f"), LocomotionDirection);
	//HandParts = EHandParts::None;
	
}
