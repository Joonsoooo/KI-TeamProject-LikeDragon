// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/MainMenu_UMG.h"
#include "Widget/WindowBase.h"
#include "Controllers/Players/RyomaController.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Characters/Players/RyomaCharacter.h"
#include "Widget/Inventory/InventoryPanel.h"


void UMainMenu_UMG::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Back)
	{
		Back->OnClicked.AddDynamic(this , &UMainMenu_UMG::QuitMainMenu);
	}
	if (MainMenu_Inventory)
	{
		MainMenu_Inventory->OnClicked.AddDynamic(this , &UMainMenu_UMG::OpenInventoryMenu);
		MainMenu_Inventory->OnHovered.AddDynamic(this , &UMainMenu_UMG::InventoryHovered);
	}
	if (MainMenu_Equipment)
	{
		MainMenu_Equipment->OnHovered.AddDynamic(this , &UMainMenu_UMG::EquipementHovered);
	}
	if (MainMenu_Status)
	{
		MainMenu_Status->OnClicked.AddDynamic(this , &UMainMenu_UMG::StatusHovered);
	}
	
	
	
	PlayerCharacter = Cast<ARyomaCharacter>(GetOwningPlayerPawn());

	WidgetTree->ForEachWidget([this] (UWidget* widget)
	{
		if (FName("MainMenuInventory") == widget->GetName())
		{
			PreInventoryPanel = Cast<UInventoryPanel>(widget);
		}
		
	});
	
}

void UMainMenu_UMG::NativeConstruct()
{
	Super::NativeConstruct();
	
}

bool UMainMenu_UMG::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}



void UMainMenu_UMG::FindShowWidgets(FName FindWidgetName)
{
	WidgetTree->ForEachWidget([this , FindWidgetName](UWidget* Widget)
{
if (FindWidgetName == Widget->GetName())
{
	Widget->SetVisibility(ESlateVisibility::Visible);
}
});
}

void UMainMenu_UMG::OpenInventoryMenu()
{
	GetWindowBaseWidget()->OnWindowState.Broadcast(EClickButton::OpenInventory);
}

void UMainMenu_UMG::QuitMainMenu()
{
	GetWindowBaseWidget()->OnWindowState.Broadcast(EClickButton::CloseMainMenu);
}

void UMainMenu_UMG::StatusHovered()
{
	SetHoveredButton(MainMenu_Status);
}

void UMainMenu_UMG::InventoryHovered()
{
	SetHoveredButton(MainMenu_Inventory);
}

void UMainMenu_UMG::EquipementHovered()
{
	SetHoveredButton(MainMenu_Equipment);
}
