// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Characters/Players/Layers/RyomaLinkedAnimLayer.h"
#include "AnimInstances/Characters/Players/RyomaCharacterAnimInstance.h"
#include "Characters/Players/RyomaCharacter.h"

void URyomaLinkedAnimLayer::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningRyomaCharacter = Cast<ARyomaCharacter>(TryGetPawnOwner());
	
	if (OwningRyomaCharacter)
	{
		OwningRyomaCharacter->Sway.BindUObject(this, &URyomaLinkedAnimLayer::SetIsSway);
		OwningRyomaCharacter->Targeting.BindUObject(this, &URyomaLinkedAnimLayer::SetIsTargeting);
		
	}

	IsSway = false;
	IsTargeting = false;
	
}

void URyomaLinkedAnimLayer::NativeThreadSafeUpdateAnimation(float DelatSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DelatSeconds);
}

URyomaCharacterAnimInstance* URyomaLinkedAnimLayer::GetRyomaAnimInstance() const
{
	//이준수, GetOwningComponent는 애님 인스턴스를 사용하는 스켈레탈 메쉬를 반환하여 그것의 애님 인스턴스에 접근
	return Cast<URyomaCharacterAnimInstance>(GetOwningComponent()->GetAnimInstance());
	
}
