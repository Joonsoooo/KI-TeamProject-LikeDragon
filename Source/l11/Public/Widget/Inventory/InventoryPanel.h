// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/Inventory/InventoryWindow.h"
#include "InventoryPanel.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRemoveItemIndex , FName , RemoveItem , UItemBase* , RemoveItemData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateInventoryPanel , FName , ItemSlotName);

class UUniformGridPanel;
class UEmptyItemSlot;
class UItemClickWindow;
class UItemBase;
class UInventoryItemSlot;
class UWrapBox;
class UInventoryComponent;
/**
 * 
 */
UCLASS()
class L11_API UInventoryPanel : public UInventoryWindow
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void RefreshInventory();
	

	UPROPERTY(VisibleAnywhere, meta = (BindWidget) , Category = "InventoryPanel")
	UUniformGridPanel* ItemSlotsGrid;
	
	UPROPERTY()
	ARyomaCharacter* PlayerCharacter;

	UPROPERTY()
	UInventoryComponent* InventoryReference;

	UPROPERTY()
	UInventoryItemSlot* ItemSlot;
	
	FOnRemoveItemIndex OnRemoveItemIndex;
	FOnUpdateInventoryPanel OnUpdateInventoryPanel;
	void HideUseItem(int32 index);

	void ItemSelected();
	
protected:
	
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,UDragDropOperation* InOperation) override;

	void SetItemSlotGrid(UUniformGridPanel* aItemSlotsGrid) {UniformGridPanel = aItemSlotsGrid;};
	
	UPROPERTY()
	TArray<UItemBase*> InventoryPanelItemsData;

	UPROPERTY()
	TArray<FName> InventorySlotsName;

	UPROPERTY()
	TArray<UInventoryItemSlot*> ItemSlotArray;
	
	UFUNCTION()
	void UseItem(FName SlotName ,UItemBase* Item);

	UPROPERTY()
	UUniformGridPanel* UniformGridPanel;
	
	int32 CurrentIndex = 0;
	int32 UseItemIndex = 0;
	int32 UpdateIndex = 0;
	
};

