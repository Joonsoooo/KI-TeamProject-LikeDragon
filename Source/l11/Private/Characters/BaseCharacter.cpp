// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "AbilitySystem/BaseAttributeSet.h"
#include "MotionWarpingComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	GetMesh()->bReceivesDecals = false; // 메시의 데칼을 끔 

	BaseAbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>(TEXT("BaseAbilitySystemComponent"));
	BaseAttributeSet = CreateDefaultSubobject<UBaseAttributeSet>(TEXT("BaseAttributeSet"));

	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return GetBaseAbilitySystemComponent();
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (BaseAbilitySystemComponent)
	{
		//김동휘, AbilitySystemComponent에 접근 어빌리티 정보 초기값 부여
		BaseAbilitySystemComponent->InitAbilityActorInfo(this, this);
	}

	//김동휘, 첫번째 인자값이 false면 디버그 모드에선 중단점이 발생하며, 게임에서 로그도 발생
	ensureMsgf(!StartupData.IsNull(), TEXT("Forgot to assigned startup data to %s"), *GetName());
}

UPawnCombatComponent* ABaseCharacter::GetPawnCombatComponent() const
{
	//김동휘, 부모 클래스에선 재구현 사용안함.
	return nullptr;
}

UPawnUIComponent* ABaseCharacter::GetPawnUIComponent() const
{
	return nullptr;
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



