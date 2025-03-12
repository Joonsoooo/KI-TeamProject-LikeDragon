// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Interfaces/PawnUIInterface.h"
#include "BaseCharacter.generated.h"

class UBaseAbilitySystemComponent;
class UBaseAttributeSet;
class UDataAsset_StartupBase;
class UMotionWarpingComponent;

UCLASS()
class L11_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface, public IPawnCombatInterface, public IPawnUIInterface
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UBaseAbilitySystemComponent* BaseAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UBaseAttributeSet* BaseAttributeSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MotionWarping")
	UMotionWarpingComponent* MotionWarpingComponent;

	//김동휘, 동기식으로 데이터를 불러온다
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "StartupData")
	TSoftObjectPtr<UDataAsset_StartupBase> StartupData;

	//김동휘, 이 액터에서 사용할 어빌리티시스템 컴포넌트를 반환 
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;

	virtual UPawnUIComponent* GetPawnUIComponent() const override;

	virtual void PossessedBy(AController* NewController) override;

public:
	FORCEINLINE UBaseAbilitySystemComponent* GetBaseAbilitySystemComponent() const { return BaseAbilitySystemComponent; }
	FORCEINLINE UBaseAttributeSet* GetBaseAttributeSet() const { return BaseAttributeSet; }
	virtual void Tick(float DeltaTime) override;
};
