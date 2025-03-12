// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DataAsset_InputConfig.generated.h"

class UInputAction;
class UInputMappingContext;



USTRUCT(BlueprintType)
struct FBaseInputActionConfig
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "chara"))
	FGameplayTag InputTag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputAction;

	bool IsValid() const
	{
		return InputTag.IsValid() && InputAction;
	}
};

/**
 * 
 */
UCLASS()
class L11_API UDataAsset_InputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (InputTag = "chara")) // 이준수, 추후에 Input으로 변경 
	TArray<FBaseInputActionConfig> NativeInputAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (InputTag = "chara"))
	TArray<FBaseInputActionConfig> AbilityInputActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (InputTag = "chara"))
	TArray< FBaseInputActionConfig> AbilityInputPressedActions; // ���ؼ�, ������ ���� ó���� ��ǲ �׼� 


	UInputAction* FindNativeInputActionByTag(const FGameplayTag& InInputTag) const;
};
