// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Characters/Players/RyomaCharacterAnimInstance.h"
#include "Characters/Players/RyomaCharacter.h"

void URyomaCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter)
	{
		OwningRyomaCharacter = Cast<ARyomaCharacter>(OwningCharacter);

		if (OwningRyomaCharacter)
		{
			OwningRyomaCharacter->RunState.BindUObject(this, &URyomaCharacterAnimInstance::SetAnimRunState);
		}
	}
}

void URyomaCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaTime)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaTime);

}
