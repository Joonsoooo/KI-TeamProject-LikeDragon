// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/InventoryWindow.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Widget/Inventory/ItemTooltip.h"
#include "Widget/Inventory/InventoryPanel.h"
#include "Widget/Inventory/InventoryWindowButton.h"

void UInventoryWindow::NativeConstruct()
{
	Super::NativeConstruct();
	
	WidgetTree->ForEachWidget([this] (UWidget* widget)
	{
		if (FName("WBP_InventoryPanel") == widget->GetName())
		{
				
			InventoryPanel = Cast<UInventoryPanel>(widget);
		}
	});
		if (InventoryPanel)
		{
			InventoryPanel->SetVisibility(ESlateVisibility::Visible);
		}
	
	
		WidgetTree->ForEachWidget([this] (UWidget* widget)
		{
			if (FName("WBP_ItemTooltip") == widget->GetName())
			{
				
				ItemToolTip = Cast<UItemTooltip>(widget);
			}
		});
		
		if (ItemToolTip)
		{
			ItemToolTip->SetVisibility(ESlateVisibility::Visible);
		}

	WidgetTree->ForEachWidget([this] (UWidget* widget)
{
	if (FName("InventoryButton") == widget->GetName())
	{
				
		InventoryWindowButton = Cast<UInventoryWindowButton>(widget);
	}
});
	if (InventoryWindowButton)
	{
		InventoryWindowButton->SetVisibility(ESlateVisibility::Visible);
	}


	OnItemHovered.AddDynamic(this , &UInventoryPanel::SetTooltipData);
	OnItemUnhovered.AddDynamic(this , &UInventoryPanel::ClearTooltipData);
}

void UInventoryWindow::SetTooltipData(UItemBase* ItemSlotData)
{
	ItemToolTip->SetTextAndIcon(ItemSlotData);
}

void UInventoryWindow::ClearTooltipData()
{
	ItemToolTip->ClearTooltip();
}



//버튼 관리
