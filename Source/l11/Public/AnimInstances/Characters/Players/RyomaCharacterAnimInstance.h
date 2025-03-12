// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/Characters/CharacterAnimInstance.h"
#include "PlayerStates/Players/RyomaState.h"

#include "RyomaCharacterAnimInstance.generated.h"

class ARyomaCharacter;
//class 
/**
 * 
 */
UCLASS()
class L11_API URyomaCharacterAnimInstance : public UCharacterAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaTime) override;


private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "RunState", meta = (AllowPrivateAccess = "true"))
	ERunState AnimRunState;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|Refrences")
	ARyomaCharacter* OwningRyomaCharacter;

public:
	UFUNCTION()
	void SetAnimRunState(ERunState OutRunState) { AnimRunState = OutRunState; }

};
