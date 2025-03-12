// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Players/RyomaCharacter.h"
#include "WIdget/WidgetBase.h"
#include "Widget/WindowBase.h"
#include "InteractionWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class L11_API UInteractionWidget : public UWindowBase
{
	GENERATED_BODY()


public:
	UPROPERTY(visibleAnywhere , Category = "InteractionWidget")
	ARyomaCharacter* PlayerReference;
	
	void UpdateWidget(const FInteractableData* UpdateInteractableData) const;
	
	const FInteractableData* GetUpdateInteractableData() const {return PickUpData;}
	void SetUpdateInteractableData(const FInteractableData* ItemData) {PickUpData = ItemData;};
	
protected:

	const FInteractableData* PickUpData = nullptr;
	
	
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
};

