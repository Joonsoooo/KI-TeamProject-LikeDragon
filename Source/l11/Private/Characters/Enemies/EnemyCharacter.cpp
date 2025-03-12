// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/EnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "DataAssets/StartupData/DataAsset_StartupBase.h"
#include "Utilities/BaseDebugHelper.h"
#include "Engine/AssetManager.h"
#include "Components/UI/EnemyUIComponent.h"
#include "Components/WidgetComponent.h"
#include "Widget/WidgetBase.h"

AEnemyCharacter::AEnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.0f;

	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>(TEXT("EnemyCombatComponent"));

	//김동휘, 생성자
	EnemyUIComponent = CreateDefaultSubobject<UEnemyUIComponent>(TEXT("EnemyUIComponent"));

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(GetMesh());
}

void AEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitEnemyStartUpData();
}

UPawnCombatComponent* AEnemyCharacter::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

UPawnUIComponent* AEnemyCharacter::GetPawnUIComponent() const
{
	return EnemyUIComponent;
}

UEnemyUIComponent* AEnemyCharacter::GetEnemyUIComponent() const
{
	return EnemyUIComponent;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (UWidgetBase* HealthWidget = Cast<UWidgetBase>(WidgetComponent->GetUserWidgetObject()))
	{
		HealthWidget->InitEnemyCreateWidget(this);
	}
}

void AEnemyCharacter::InitEnemyStartUpData()
{
	if (StartupData.IsNull())
	{
		return;
	}
	
	//Startup Data를 비동기 로딩으로 불러온다.
	UAssetManager::GetStreamableManager().RequestAsyncLoad
	(
		StartupData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda
		(
			[this]()
			{
				if (UDataAsset_StartupBase* LoadedData = StartupData.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(BaseAbilitySystemComponent);
					Debug::Print(TEXT("Enemy Start Up Data Loaded"), FColor::Green);
				}
			}
		)
	);
}

void AEnemyCharacter::GetCurrentBossHealth()
{
	if (GetCurrentedBossHealth.IsBound())
	{
		GetCurrentedBossHealth.Broadcast();
	}
}

