// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/InventoryPanel.h"

#include "Algo/Replace.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Characters/Players/RyomaCharacter.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/Inventory/InventoryComponent.h"
#include "Items/ItemBase.h"
#include "Widget/Inventory/InventoryItemSlot.h"
#include "Components/UniformGridPanel.h"
#include "Widget/ShopMainMenu.h"
#include "Widget/Inventory/MainMenu_UMG.h"
#include "Widget/Inventory/ShopNPC.h"


void UInventoryPanel::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	PlayerCharacter = Cast<ARyomaCharacter>(GetOwningPlayerPawn());
	if (PlayerCharacter)
	{
		InventoryReference = PlayerCharacter->GetInventory();
		if (InventoryReference)
		{
			InventoryReference->OnInventoryUpdate.AddUObject(this , &UInventoryPanel::RefreshInventory);
		}
	}

	WidgetTree->ForEachWidget([this](UWidget* FindGridPanel)
	{
		if (FName("ItemSlotsGrid") == FindGridPanel->GetName())
		{
			ItemSlotsGrid = Cast<UUniformGridPanel>(FindGridPanel);
			SetItemSlotGrid(ItemSlotsGrid);
			if (ItemSlotsGrid)
			{
				for (int32 i = 0 ; ItemSlotsGrid->GetChildrenCount() > i ; i++)
				{
					ItemSlot = Cast<UInventoryItemSlot>(ItemSlotsGrid->GetChildAt(i));
					ItemSlotArray.Add(ItemSlot);
					
				}
				
			}
		
		}
	});

	for (int32 i = 0; i < ItemSlotArray.Num(); i++)
	{
		ItemSlotArray[i]->SetVisibility(ESlateVisibility::Hidden);
		InventorySlotsName.Add(*ItemSlotArray[i]->GetName());
		
	}

	
	
	
	OnRemoveItemIndex.AddDynamic(this, &UInventoryPanel::UseItem);
	
}

void UInventoryPanel::NativeConstruct()
{
	Super::NativeConstruct();
}


bool UInventoryPanel::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                   UDragDropOperation* InOperation)
{
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UInventoryPanel::RefreshInventory()
{
	if (InventoryReference)
	{
		InventoryPanelItemsData.Reset();
		for (int32 i = 0 ; i < InventoryReference->GetInventoryContents().Num() ; i++)
		{
			InventoryPanelItemsData.Add(InventoryReference->GetInventoryContents()[i]);
		}
		
		for (int32 i = 0 ; i < InventoryPanelItemsData.Num(); i++)
		{
			ItemSlotArray[i]->SetItemReference(InventoryPanelItemsData[i]);
			ItemSlotsGrid->GetChildAt(i)->SetVisibility(ESlateVisibility::Visible);
			ItemSlotsGrid->GetChildAt(i)->SetRenderOpacity(1);
			ItemSlotArray[i]->SetUpdateIcon(InventoryPanelItemsData[i]);
		}
		
	}


}

void UInventoryPanel::UseItem(FName SlotName , UItemBase* Item)
{
	
	UE_LOG(LogTemp, Error, TEXT("UseItemIndex ") );
	for (int32 i = 0; InventorySlotsName.Num() > i ; i++)
	{
		//사용한 아이템 인덱스
		if (InventorySlotsName[i] == SlotName)
		{
			UseItemIndex = i;
		}
	}
	
	InventoryReference->SetInventoryContents(UseItemIndex);
	

	ItemSlotArray[UseItemIndex]->SetRenderOpacity(0);
	ItemSlotArray[UseItemIndex]->SetVisibility(ESlateVisibility::HitTestInvisible);
	
	GetWindowBaseWidget()->MainMenu_UMG->PreInventoryPanel->ItemSlotsGrid->GetChildAt(UseItemIndex)->SetVisibility(ESlateVisibility::HitTestInvisible);
	GetWindowBaseWidget()->MainMenu_UMG->PreInventoryPanel->ItemSlotsGrid->GetChildAt(UseItemIndex)->SetRenderOpacity(0);

	PlayerCharacter->SellNpc->ShopMainMenu->ShopInventoryPanel->ItemSlotsGrid->GetChildAt(UseItemIndex)->SetVisibility(ESlateVisibility::HitTestInvisible);
	PlayerCharacter->SellNpc->ShopMainMenu->ShopInventoryPanel->ItemSlotsGrid->GetChildAt(UseItemIndex)->SetRenderOpacity(0);
	
}


void UInventoryPanel::HideUseItem(int32 index)
{


}

void UInventoryPanel::ItemSelected()
{
	for (int32 i = 0; ItemSlotArray.Num() > i ; i++)
	{
		if (ItemSlotArray[i]->IsHovered())
		{
			ItemSlotArray[i]->SetClick();
		}

	}
}
