// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Players/RyomaGameplayAbility_Hact.h"

#include "AbilitySystem/BaseGamePlayTags.h"
#include "Characters/Players/RyomaCharacter.h"
#include "Utilities/BaseFunctionLibrary.h"


URyomaGameplayAbility_Hact::URyomaGameplayAbility_Hact()
{
}

bool URyomaGameplayAbility_Hact::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{

	float HactCurrentValue = 0.0f;
	
	if (ARyomaCharacter* RyomaCharacter = Cast<ARyomaCharacter>(ActorInfo->AvatarActor))
	{
		if (UBaseAbilitySystemComponent* ASC = RyomaCharacter->GetBaseAbilitySystemComponent())
		{
			HactCurrentValue = ASC->GetNumericAttribute(HactAttribute);
		}
	}

	bool Istrue  = UBaseFunctionLibrary::NativeActorHasTag(ActorInfo->AvatarActor.Get(), BaseGameplayTags::Chara_Event_Attack_Hact);

	if ( Istrue && HactCurrentValue == 1.0f )
	{
		//UE_LOG(LogTemp, Warning, TEXT("True, %f"), HactCurrentValue);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("False, %f"), HactCurrentValue);
	}
	
	return  (Istrue && HactCurrentValue >= 1.0) ? true : false;
	
	
	//return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

float URyomaGameplayAbility_Hact::GetHactCurrentValue() const
{
	
	return 0.0f;
}




