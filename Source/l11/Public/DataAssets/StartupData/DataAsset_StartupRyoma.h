// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartupData/DataAsset_StartupBase.h"
#include "DataAsset_StartupRyoma.generated.h"

struct FRyomaAbilitySet;

/**
 * 
 */
UCLASS()
class L11_API UDataAsset_StartupRyoma : public UDataAsset_StartupBase
{
	GENERATED_BODY()

protected:
	virtual void GiveToAbilitySystemComponent(UBaseAbilitySystemComponent* ASC, int32 Level = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "StartupData", meta=(TitleProperty="InputTag"))
	TArray<FRyomaAbilitySet> RyomaStartupAbilitySets;

	
	
};
