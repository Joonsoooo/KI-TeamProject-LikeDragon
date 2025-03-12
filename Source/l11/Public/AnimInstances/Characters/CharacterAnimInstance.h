// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/BaseAnimInstance.h"
#include "BaseType/BaseEnumType.h"

#include "CharacterAnimInstance.generated.h"


class ABaseCharacter;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class L11_API UCharacterAnimInstance : public UBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DelatSeconds) override;

protected:
	UPROPERTY()
	ABaseCharacter* OwningCharacter;

	UPROPERTY()
	UCharacterMovementComponent* OwningMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Locomotion")
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Locomotion")
	bool bHasAcceleration;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Locomotion")
	float LocomotionDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hand")
	EHandParts HandParts;
};
