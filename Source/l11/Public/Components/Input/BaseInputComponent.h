// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "BaseInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class L11_API UBaseInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func);

	
	// 이준수, 눌렀을 때 Pressed, Released 둘 다 처리
	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputRelesedFunc);

	// 이준수 눌렀을 때 Pressed만 처리
	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputPressedAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc);

};

template<class UserObject, typename CallbackFunc>
inline void UBaseInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
	checkf(InInputConfig, TEXT("Input config data asset is null, can not proceed with binding"));
	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
	}
}

template<class UserObject, typename CallbackFunc>
inline void UBaseInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputRelesedFunc)
{
	checkf(InInputConfig, TEXT("Input config data asset is null,can not proceed with binding"));

	for (const FBaseInputActionConfig& AbilityInputActionConfig : InInputConfig->AbilityInputActions)
	{
		if (!AbilityInputActionConfig.IsValid()) continue;

		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc, AbilityInputActionConfig.InputTag);
		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, InputRelesedFunc, AbilityInputActionConfig.InputTag);
	}
}

template<class UserObject, typename CallbackFunc>
inline void UBaseInputComponent::BindAbilityInputPressedAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc)
{
	checkf(InInputConfig, TEXT("Input config data asset is null,can not proceed with binding"));

	for (const FBaseInputActionConfig& AbilityInputPressedActionConfig : InInputConfig->AbilityInputPressedActions)
	{
		if (!AbilityInputPressedActionConfig.IsValid()) continue;

		BindAction(AbilityInputPressedActionConfig.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc, AbilityInputPressedActionConfig.InputTag);
	}

}

