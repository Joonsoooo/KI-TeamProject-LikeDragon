// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BaseAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/BaseGamePlayTags.h"
#include "Characters/Players/RyomaCharacter.h"
#include "Components/UI/PawnUIComponent.h"
#include "Components/UI/RyomaUIComponent.h"
#include "GameStates/DefaultGameState.h"
#include "Utilities/BaseDebugHelper.h"
#include "Utilities/BaseFunctionLibrary.h"
#include "Interfaces/PawnUIInterface.h"
#include "Widget/DamageIndicator.h"

UBaseAttributeSet::UBaseAttributeSet()
{
	InitHealthCurrent(1.f);
	InitHealthMax(1.f);
	InitStaminaCurrent(1.f);
	InitStaminaMax(1.f);
	InitHactCurrent((1.f));
	InitHactMax((1.f));
	InitAttackKatana(1.f);
	InitAttackGun(1.f);
	InitCriticalChance(1.f);
	InitCriticalMultiplier(1.f);
	InitDefense(1.f);

	InitDamageTaken(1.f);
}

void UBaseAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{

	if (!CachedUIInterface.IsValid())
	{
		// 액터가 IPawnUIInterface 타입을 가지고 있으면 생성 
		CachedUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
	}

	checkf(CachedUIInterface.IsValid(), TEXT("%s does not Implementation IPawnUIInterface."), *Data.Target.GetAvatarActor()->GetActorLabel());

	//이준수, 가져온 인터페이스를 통해 폰ui컴포넌트를 가져옴 
	UPawnUIComponent* PawnUIComponent = CachedUIInterface->GetPawnUIComponent();
	checkf(PawnUIComponent, TEXT("Can not Load PawnUIComponent from %s"), *Data.Target.GetAvatarActor()->GetActorLabel());

	//URyomaUIComponent* RyomaUIComponent = CachedUIInterface->GetRyomaUIComponent();
	//checkf(RyomaUIComponent, TEXT("Can not Load RyomaUIComponent from %s"), *Data.Target.GetAvatarActor()->GetActorLabel());
	
	// 이준수, GameplayEffect가 속성이 변경되고 Data에는 변경된 속성과 변경된 양이 담겨있음
	//이준수, 만약 체력이 변동되었다면 폰ui컴포넌트에 있는 델리게이트를 브로드캐스트
	if (Data.EvaluatedData.Attribute == GetHealthCurrentAttribute())
	{
		// 이준수, 최종 값을 수정 
		const float NewHealthCurrent = FMath::Clamp(GetHealthCurrent(), 0.0f, GetHealthMax());
		SetHealthCurrent(NewHealthCurrent);

		//김동휘, TODO:: UI에 값을 전달
		PawnUIComponent->OnHealthCurrentChanged.Broadcast(GetHealthCurrent() / GetHealthMax());
	}

	if (Data.EvaluatedData.Attribute == GetStaminaCurrentAttribute())
	{
		if (URyomaUIComponent* RyomaUIComponent = CachedUIInterface->GetRyomaUIComponent())
		{
			if (GetHactCurrent() >= GetHactMax())
			{
				SetStaminaCurrent(GetStaminaMax() / 3);
			}
			else
			{
				const float NewStaminaCurrent = FMath::Clamp(GetStaminaCurrent(), 0.0f, GetStaminaMax() / 3.0f);
				SetStaminaCurrent(NewStaminaCurrent);
			}

			RyomaUIComponent->OnStaminaCurrentChanged.Broadcast(GetStaminaCurrent() / (GetStaminaMax() / 3.0f));
		}
		
	}

	if (Data.EvaluatedData.Attribute == GetHactCurrentAttribute())
	{
		if (URyomaUIComponent* RyomaUIComponent = CachedUIInterface->GetRyomaUIComponent())
		{
			if (GetHactCurrent() >= GetHactMax())
			{
				SetHactCurrent(GetHactMax());
			}
			else
			{
				const float NewHactCurrent = FMath::Clamp(GetHactCurrent(), 0.0f, GetHactMax() - 1.0f);
				SetHactCurrent(NewHactCurrent);
			}
			
			RyomaUIComponent->OnHactCurrentChanged.Broadcast(GetHactCurrent());
			
		}
	}

	// 이준수, 최종 데미지 적용 값을 수정 및 스태미너 회복 
	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float BeforeHp = GetHealthCurrent();
		const float Damage = GetDamageTaken();

		PawnUIComponent->OnDamageCurrentChanged.Broadcast(Damage);

		FString BPPath = TEXT("/Game/Like/BP_/Widget/Damage/BP_DamageIndicator.BP_DamageIndicator_C");
		UClass* BPClass = LoadObject<UClass>(nullptr, *BPPath);
		if (!BPClass)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to load BP_Damage class from path: %s"), *BPPath);
			return;
		}

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		// 스폰 위치와 회전 설정
		FTransform SpawnTransform(Data.Target.GetAvatarActor()->GetActorRotation(), Data.Target.GetAvatarActor()->GetActorLocation());

		
		// SpawnActorDeferred를 사용하여 스폰 (초기화 지연)
		ADamageIndicator* SpawnedActor = GetWorld()->SpawnActorDeferred<ADamageIndicator>(BPClass, SpawnTransform);

		if (!UBaseFunctionLibrary::NativeActorHasTag(Data.Target.GetAvatarActor(), BaseGameplayTags::Shared_Status_Dead))
		{
			if (SpawnedActor)
			{
				// 초기화 전에 Damage 값 설정
				SpawnedActor->Damage = Damage;

				// 초기화 완료
				SpawnedActor->FinishSpawning(SpawnTransform);
			}
			else
			{
				//UE_LOG(LogTemp, Error, TEXT("Failed to spawn actor of class BP_DamageIndicator."));
			}
		}

		
		// 이준수, 0.0f <= BeforeHp - Damage <= GetHealthMax 값으로 적용 
		const float NewCurrentHp = FMath::Clamp(BeforeHp - Damage, 0.0f, GetHealthMax());
		SetHealthCurrent(NewCurrentHp);

		const FString DebugString = FString::Printf(TEXT("Before Hp: %f, Damage: %f, NewCurrentHp : %f"), BeforeHp, Damage, NewCurrentHp);
		//Debug::Print(DebugString, FColor::Green);
        
		//TODO:: Ui에 값을 전달
		PawnUIComponent->OnHealthCurrentChanged.Broadcast(GetHealthCurrent() / GetHealthMax());
		
		//Character Death Process
		if (NewCurrentHp == 0.f)
		{
			if (AEnemyCharacter* DeathEnemy = Cast<AEnemyCharacter>(Data.Target.GetAvatarActor()))
			{
				if (!UBaseFunctionLibrary::NativeActorHasTag(Data.Target.GetAvatarActor(), BaseGameplayTags::Shared_Status_Dead))
				{
					UBaseFunctionLibrary::AddPlaygameTagToActor(Data.Target.GetAvatarActor(), BaseGameplayTags::Shared_Status_Dead);
					
					if (ADefaultGameState* DefaultsGameState = Cast<ADefaultGameState>(GetWorld()->GetGameState()))
					{
						DefaultsGameState->DetectedCombatEnemy -= 1;
						UE_LOG(LogTemp, Warning, TEXT("%d"), DefaultsGameState->DetectedCombatEnemy);
					
						if (DefaultsGameState->DetectedCombatEnemy == 0)
						{
							DefaultsGameState->SetCombatGameState(ECombatGameState::BattleEnd);
						}
					}
				}
			}
			else
			{
				UBaseFunctionLibrary::AddPlaygameTagToActor(Data.Target.GetAvatarActor(), BaseGameplayTags::Shared_Status_Dead);
			}
		}
	}

	if (Data.EvaluatedData.Attribute == GetStaminaTakenAttribute())
	{
		//UE_LOG(LogTemp, Warning, TEXT("GetStaminaTaken"));
		
		const float Damage = GetStaminaTaken();
		// 데미지를 입히면 스태미너 회복 
		const float BeforeStamina = GetStaminaCurrent();
		const float BeforeHact = GetHactCurrent();
		const float NewStaminaCurrent = Damage + BeforeStamina;
		
		if (NewStaminaCurrent >= GetStaminaMax() / 3)
		{
			//UE_LOG(LogTemp, Warning, TEXT("True GetStaminaTaken"));

			const float NewHactCurrent = BeforeHact + 1.0f;
			SetHactCurrent(NewHactCurrent);

			if (URyomaUIComponent* RyomaUIComponent = CachedUIInterface->GetRyomaUIComponent())
			{
				RyomaUIComponent->OnHactCurrentChanged.Broadcast(NewHactCurrent);
			}
			
			SetStaminaCurrent(0.f);
			
			if (URyomaUIComponent* RyomaUIComponent = CachedUIInterface->GetRyomaUIComponent())
			{
				RyomaUIComponent->OnStaminaCurrentChanged.Broadcast(GetStaminaCurrent() / (GetStaminaMax() / 3.0f));
			}
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("False GetStaminaTaken"));

			SetStaminaCurrent(NewStaminaCurrent);

			if (URyomaUIComponent* RyomaUIComponent = CachedUIInterface->GetRyomaUIComponent())
			{
				RyomaUIComponent->OnStaminaCurrentChanged.Broadcast(GetStaminaCurrent() / (GetStaminaMax() / 3.0f));
			}
		}
	}

	if (Data.EvaluatedData.Attribute == GetHactTakenAttribute())
	{
		const float HactCount = GetHactTaken();
		const float BeforeHact = GetHactCurrent();

		const float NewHactCurrent = BeforeHact - HactCount;
		SetHactCurrent(NewHactCurrent);
		
		if (URyomaUIComponent* RyomaUIComponent = CachedUIInterface->GetRyomaUIComponent())
		{
			RyomaUIComponent->OnHactCurrentChanged.Broadcast(NewHactCurrent);
		}
	}

}
