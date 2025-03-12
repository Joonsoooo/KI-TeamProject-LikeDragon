// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/ItemClickWindow.h"

#include "Components/Button.h"
#include "Widget/Inventory/InventoryItemSlot.h"


void UItemClickWindow::NativeConstruct()
{
	Super::NativeConstruct();
	NoButton->OnClicked.AddDynamic(this ,&UItemClickWindow::HideClickWindow);

	
}

void UItemClickWindow::HideClickWindow()
{
	SetVisibility(ESlateVisibility::Hidden);
}
