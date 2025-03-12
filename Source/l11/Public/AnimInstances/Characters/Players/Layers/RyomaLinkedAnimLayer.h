// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/BaseAnimInstance.h"
#include "RyomaLinkedAnimLayer.generated.h"

class URyomaCharacterAnimInstance;
class ARyomaCharacter;
/**
 * 
 */
UCLASS()
class L11_API URyomaLinkedAnimLayer : public UBaseAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	
	UFUNCTION(BlueprintPure, meta = (NotBlueprintThreadSafe))
	URyomaCharacterAnimInstance* GetRyomaAnimInstance() const;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|Refrences")
	ARyomaCharacter* OwningRyomaCharacter;
protected:

public:
	//Setter
	UFUNCTION()
	void SetIsSway(bool OutIsSway) { IsSway = OutIsSway; }
	void SetIsTargeting(bool OutTargeting) { IsTargeting = OutTargeting; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimData", meta = (AllowPrivateAccess = "true"))
	bool IsSway;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimData", meta = (AllowPrivateAccess = "true"))
	bool IsTargeting;
};
