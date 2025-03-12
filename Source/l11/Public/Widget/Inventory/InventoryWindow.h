// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "Widget/WindowBase.h"
#include "InventoryWindow.generated.h"

class UInventoryWindowButton;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemSlotHovered, UItemBase*, SlotItemData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemSlotUnhovered);

class UItemTooltip;
class UInventoryPanel;
/**
 * 
 */
UCLASS()
class L11_API UInventoryWindow : public UWindowBase
{
	GENERATED_BODY()

	public:

	
	UPROPERTY()
	UInventoryPanel* InventoryPanel;
	
	UPROPERTY()
	UItemTooltip* ItemToolTip;

	UPROPERTY()
	UInventoryWindowButton* InventoryWindowButton;
	
	FOnItemSlotHovered OnItemHovered;
	FOnItemSlotUnhovered OnItemUnhovered;


protected:
	
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void SetTooltipData(UItemBase* ItemSlotData);
	UFUNCTION()
	void ClearTooltipData();

	

};

