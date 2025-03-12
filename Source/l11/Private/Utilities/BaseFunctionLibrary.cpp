// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/BaseFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "Interfaces/PawnCombatInterface.h"
#include "BaseType/BaseEnumType.h"
#include "GenericTeamAgentInterface.h"
#include "AbilitySystem/BaseGamePlayTags.h"
#include "Kismet/KismetMathLibrary.h"
#include "Utilities/BaseDebugHelper.h"

UBaseAbilitySystemComponent* UBaseFunctionLibrary::NativeGetAbilitySystemComponentFromActor(AActor* Actor)
{
	check(Actor);

	return CastChecked<UBaseAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor));
}

void UBaseFunctionLibrary::AddPlaygameTagToActor(AActor* Actor, FGameplayTag Tag)
{
	UBaseAbilitySystemComponent* ASC = NativeGetAbilitySystemComponentFromActor(Actor);
	if (!ASC->HasMatchingGameplayTag(Tag))
	{
		ASC->AddLooseGameplayTag(Tag);
	}
}

void UBaseFunctionLibrary::RemovePlaygameTagFromActor(AActor* Actor, FGameplayTag Tag)
{
	UBaseAbilitySystemComponent* ASC = NativeGetAbilitySystemComponentFromActor(Actor);
	if (!ASC->HasMatchingGameplayTag(Tag))
	{
		ASC->RemoveLooseGameplayTag(Tag);
	}
}

bool UBaseFunctionLibrary::NativeActorHasTag(AActor* Actor, FGameplayTag Tag)
{
	UBaseAbilitySystemComponent* ASC = NativeGetAbilitySystemComponentFromActor(Actor);
	return ASC->HasMatchingGameplayTag(Tag);
}

void UBaseFunctionLibrary::BP_HasTag(AActor* Actor, FGameplayTag Tag, EBaseConfirmType& OutType)
{
	if (!Actor)
	{
		OutType = EBaseConfirmType::No;
		return;
	}
	OutType = NativeActorHasTag(Actor, Tag) ? EBaseConfirmType::Yes : EBaseConfirmType::No;
}

UPawnCombatComponent* UBaseFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* Actor)
{
	check(Actor);

	// 이준수, 해당 액터의 PawnCombatInterface를 반환 
	if (IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(Actor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}
	return nullptr;
}

UPawnCombatComponent* UBaseFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* Actor, EBaseValidType& OutValidType)
{
	if (!Actor)
	{
		return nullptr;
	}
	
	UPawnCombatComponent* CombatComponent = NativeGetPawnCombatComponentFromActor(Actor);
	OutValidType = CombatComponent ? EBaseValidType::Valid : EBaseValidType::Invalid;

	return CombatComponent;
}

bool UBaseFunctionLibrary::IsTargetPawnHostile(APawn* OwningPawn, APawn* TargetPawn)
{
	check(OwningPawn && TargetPawn);

	IGenericTeamAgentInterface* OwningTeamAgent = Cast<IGenericTeamAgentInterface>(OwningPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if (OwningTeamAgent && TargetTeamAgent)
	{
		return OwningTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}

	return false;
}

bool UBaseFunctionLibrary::IsValidBlock(AActor* Attacker, AActor* Defender)
{
	check(Attacker && Defender);

	//김동휘, 내적을 활용해 플레이어와 적이 마주보고 있는지 판단한다. 마주보고 있으면 -1에 가까운 값을 반환하고, 뒤를 보면 1에 가까운 값을 반환한다.
	const float DotResult = FVector::DotProduct(Attacker->GetActorForwardVector(), Defender->GetActorForwardVector());

	const FString DebugString = FString::Printf(TEXT("Dot Result: %f %s"), DotResult, DotResult < 0.1f ? TEXT("Valid Block") : TEXT("InValid Block"));

	Debug::Print(DebugString, DotResult < 0.1f ? FColor::Green : FColor::Red);

	return DotResult < 0.1f;
}

bool UBaseFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(AActor* Instigator, AActor* TargetActor, const FGameplayEffectSpecHandle& OutSpecHandle)
{
	UBaseAbilitySystemComponent* SourceASC = NativeGetAbilitySystemComponentFromActor(Instigator);
	UBaseAbilitySystemComponent* TargetASC = NativeGetAbilitySystemComponentFromActor(TargetActor);

	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = SourceASC->ApplyGameplayEffectSpecToTarget(*OutSpecHandle.Data, TargetASC);

	return ActiveGameplayEffectHandle.WasSuccessfullyApplied();
}

FGameplayTag UBaseFunctionLibrary::ComputeHitReactDirectionTag(AActor* Attacker, AActor* HitActor,
	float& OutAngleDifference)
{
	check(Attacker && HitActor);

	const FVector HitForward = HitActor->GetActorForwardVector();
	const FVector HitToAttackerNormalized = (Attacker->GetActorLocation() - HitActor->GetActorLocation()).GetSafeNormal();

	const float DotResult = FVector::DotProduct(HitForward, HitToAttackerNormalized);
	OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);

	const FVector CrossResult = FVector::CrossProduct(HitForward, HitToAttackerNormalized);

	if (CrossResult.Z < 0.f)
	{
		OutAngleDifference *= -1.f;
	}

	if (OutAngleDifference >= -45.f && OutAngleDifference <= 45.f)
	{
		return BaseGameplayTags::Shared_Status_HitReact_Front;
	}
	else if (OutAngleDifference < -45.f && OutAngleDifference > -135.0f)
	{
		return BaseGameplayTags::Shared_Status_HitReact_Left;
	}
	else if (OutAngleDifference > 45.f && OutAngleDifference < 135.0f)
	{
		return BaseGameplayTags::Shared_Status_HitReact_Right;
	}
	else if (OutAngleDifference <= -135.0f || OutAngleDifference >= 135.0f)
	{
		return BaseGameplayTags::Shared_Status_HitReact_Back;
	}
	
	return BaseGameplayTags::Shared_Status_HitReact_Front;
}
