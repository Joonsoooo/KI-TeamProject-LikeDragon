// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/Inventory/InventoryWindow.h"
#include "ItemTooltip.generated.h"

class UItemBase;
class UTextBlock;
class UInventoryItemSlot;
/**
 * 
 */
UCLASS()
class L11_API UItemTooltip : public UInventoryWindow 
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	UInventoryItemSlot* InventoryBeingHovered;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Type;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DamageValue;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* UsageText;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Description;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxStackSize;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* StackSizeValue;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SellValue;

	UPROPERTY(meta = (BindWidget))
	UImage* Star;
	
	UPROPERTY(meta = (BindWidget))
	UImage* Star_1;

	UPROPERTY(meta = (BindWidget))
	UImage* Star_2;

	UPROPERTY(meta = (BindWidget))
	UImage* Star_3;

	UPROPERTY(meta = (BindWidget))
	UImage* Star_4;

	UPROPERTY(meta = (BindWidget))
	UImage* Star_5;

	UPROPERTY(meta = (BindWidget))
	UImage* Star_6;

	UPROPERTY(meta = (BindWidget))
	UImage* Star_7;

	UPROPERTY(meta = (BindWidget))
	UImage* Star_8;

	UPROPERTY(meta = (BindWidget))
	UImage* Star_9;

	UPROPERTY(meta = (BindWidget))
	UImage* TooltipImage;
	
	void ChangedStarImage(int8 Quality);
	void ClearTooltip();
	
	UFUNCTION()
	void SlotItemQuality(EItemQuality Quality);
	
	void SetTextAndIcon(UItemBase* ItemSlotData);
protected:
	TArray<UImage*> StarImages;
	
	virtual void NativeConstruct() override;

	UPROPERTY()
	UItemBase* ItemReference;
	
};
