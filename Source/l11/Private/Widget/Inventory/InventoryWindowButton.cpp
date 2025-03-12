// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/InventoryWindowButton.h"

#include "Components/Button.h"

void UInventoryWindowButton::NativeConstruct()
{
	Super::NativeConstruct();

	InventoryBack->OnClicked.AddDynamic(this , &UInventoryWindowButton::CloseInventoryWindow);
}

void UInventoryWindowButton::CloseInventoryWindow()
{
	UE_LOG(LogTemp, Warning, TEXT("Close Inventory Window"));
	GetWindowBaseWidget()->OnWindowState.Broadcast(EClickButton::CloseInventory);
}
