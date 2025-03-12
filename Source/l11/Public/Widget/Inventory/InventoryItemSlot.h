// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "Widget/WindowBase.h"
#include "InventoryItemSlot.generated.h"

class UItemClickWindow;
DECLARE_DYNAMIC_DELEGATE(FOnInventoryItemClick);

class UBorder;
class UItemInfo;
class UItemBase;
/**
 * 
 */

UCLASS()
class L11_API UInventoryItemSlot : public UWindowBase
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetItemReference(UItemBase* ItemIn){ItemReference = ItemIn;}
	FORCEINLINE UItemBase* GetItemReference() const { return ItemReference;}

	UPROPERTY(meta = (BindWidget))
	UButton* SlotButton;

	FOnInventoryItemClick OnClick;

	UPROPERTY(EditAnywhere , Category = "ItemClickWindow")
	TSubclassOf<UItemClickWindow> BP_ItemClickWindow;

	UPROPERTY()
	UItemClickWindow* ItemClickWindow;

	UFUNCTION()
	void SetUpdateIcon(UItemBase* UpdateItem);
	
	UFUNCTION()
	void SetClick();
protected:

	int32 SlotIndex;
	
	UPROPERTY(VisibleAnywhere , Category = "InventorySlot" )
	UItemBase* ItemReference;

	UPROPERTY(meta = (BindWidget))
	UBorder* ItemBorder;
	
	UPROPERTY(meta = (BindWidget))
	UImage* ItemIcon;
	
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;



	UFUNCTION()
	void SlotHovered();

	UFUNCTION()
	void SlotUnHovered();


	void ItemSlotHidden();

	UFUNCTION()
	void UseSlotItem();
};
