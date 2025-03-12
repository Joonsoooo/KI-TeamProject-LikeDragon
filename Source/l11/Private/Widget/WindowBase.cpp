// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/WindowBase.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/Inventory/MainMenu_UMG.h"
#include "Widget/Interaction/InteractionWidget.h"
#include "Widget/Inventory/InventoryWindow.h"
#include "Widget/ShopMainMenu.h"
#include "Widget/Inventory/InventoryPanel.h"
#include "Widget/Inventory/ShopNPC.h"


void UWindowBase::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (BP_MainMenu_UMG)
	{
		UE_LOG(LogTemp, Warning, TEXT("UWindowBase::NativeConstruct"));
		MainMenu_UMG = CreateWidget<UMainMenu_UMG>(GetWorld() , BP_MainMenu_UMG);
		if (MainMenu_UMG)
		{
			MainMenu_UMG->AddToViewport(3);
			MainMenu_UMG->SetVisibility(ESlateVisibility::Collapsed);
			MainMenu_UMG->OnClickButton.AddUObject(this , &UWindowBase::ToggleMainMenu);
		}
		
	}
	
	if (BP_InteractionWidget)
	{
		
		InteractionWidget = CreateWidget<UInteractionWidget>(this , BP_InteractionWidget);
		if (true)
		{UE_LOG(LogTemp, Warning, TEXT("UWindowBase::InteractionWidget"));
			InteractionWidget->AddToViewport();
			InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
			
		}
		
	}
	
	if (BP_InventoryWindow)
	{
		InventoryWindow = CreateWidget<UInventoryWindow>(this , BP_InventoryWindow);
		if (InventoryWindow)
		{
			InventoryWindow->AddToViewport(2);
			InventoryWindow->SetVisibility(ESlateVisibility::Collapsed);
			//InventoryWindow->Back->OnClicked.AddDynamic()
			
		}
	}


	if (!PlayerRyomaCharacter)
	{
		ACharacter* PlayerCharacter = Cast<ACharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
		PlayerRyomaCharacter =Cast<ARyomaCharacter>(PlayerCharacter);
		if (PlayerRyomaCharacter)
		{
			ShopNPC = Cast<AShopNPC>(PlayerRyomaCharacter->SellNpc);
		
		}
	}

	
	OnWindowState.AddDynamic(this ,&UWindowBase::SetWidgetVisibility);
	OnShopWindowVisible.AddDynamic(this ,&UWindowBase::ShopMenuVisible);
	
	
}

void UWindowBase::ShowInteractionWidget()
{
	if (InteractionWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("UWindowBase::ShowInteractionWidget"));
		bIsMenuVisible = true;
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UWindowBase::HideInteractionWidget()
{
	if (InteractionWidget)
	{
		
		bIsMenuVisible = false;
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	
}

void UWindowBase::UpdateInteractionWidget(const FInteractableData* CurrentInteractableData) const
{
	if (InteractionWidget)
	{
		if (InteractionWidget->GetVisibility() == ESlateVisibility::Collapsed)
		{
			InteractionWidget->SetVisibility(ESlateVisibility::Visible);
		}
		InteractionWidget->UpdateWidget(CurrentInteractableData);
		InteractionWidget->SetUpdateInteractableData(CurrentInteractableData);
	}

}


void UWindowBase::ShopMenuVisible(bool ShopWindowState)
{
	
	bIsShopMenuVisible = ShopWindowState;
	if (ShopWindowState)
	{
		SetWidgetVisibility(OpenShopMainMenu);
		FInputModeGameAndUI InputMode;
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.0001f);
		GetWorld()->GetFirstPlayerController()->SetInputMode(InputMode);
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	}
	else
	{
		SetWidgetVisibility(CloseShopMenu);
		FInputModeGameAndUI InputMode;
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
		GetWorld()->GetFirstPlayerController()->SetInputMode(InputMode);
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	}
}


void UWindowBase::SetWidgetVisibility(EClickButton ButtonState)
{
	
	switch (ButtonState) {
		
	case EClickButton::OpenInventory:
		UE_LOG(LogTemp, Warning, TEXT("UWindowBase::SetWidgetVisibility : OpenInventory"));
		OnRyomaStatus.Broadcast(OpenInventory);
		ShowInventory();
		
		break;
		
	case EClickButton::CloseInventory:
		UE_LOG(LogTemp, Warning, TEXT("UWindowBase::SetWidgetVisibility : CloseInventory"));
		OnRyomaStatus.Broadcast(CloseInventory);
		HideInventory();
	
		break;
	case EClickButton::CloseMainMenu:
		ToggleMainMenu();
		break;

	case EClickButton::OpenMainMenu:
		ToggleMainMenu();
		
		break;
		
	case OpenShopMainMenu:
		
		OnRyomaStatus.Broadcast(OpenShopMainMenu);
	
		break;
	case CloseShopMenu:
		OnRyomaStatus.Broadcast(CloseShopMenu);
	
		break;
	}
}

void UWindowBase::MainWindowsSelect()
{
	if (bIsMenuVisible)
	{
		if (MainMenu_UMG->GetHoveredButton())
		{
			MainMenu_UMG->GetHoveredButton()->OnClicked.AddDynamic(this, &UWindowBase::ShowInventory);
		}
		
	}
	else if (bIsInventoryVisible)
	{
		InventoryWindow->InventoryPanel->ItemSelected();
	}
	else if (bIsShopMenuVisible)
	{
		for (int32 i = 0 ; i < ShopNPC->ShopMainMenu->FoodItemArray.Num(); i++)
		{
			if (ShopNPC->ShopMainMenu->FoodItemArray[i]->IsHovered())
			{
				ShopNPC->ShopMainMenu->OpenSellWindow();
			}
		}
		
	}
	
}

void UWindowBase::MainWindowsESC()
{
	if (bIsMenuVisible)
	{
		SetWidgetVisibility(EClickButton::CloseMainMenu);
	}
	else if (bIsInventoryVisible)
	{
		SetWidgetVisibility(EClickButton::CloseInventory);
	}
	if (bIsShopMenuVisible)
	{	UE_LOG(LogTemp, Warning, TEXT("UWindowBase::MainWindowsESC"));
		
		if (PlayerRyomaCharacter)
		{
		
			ShopNPC->QuietShopMainMenu();
		}
	}
}

UWindowBase* UWindowBase::GetWindowBaseWidget()
{
	ACharacter* PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetCharacter();
	if (ARyomaCharacter* MyCharacter = Cast<ARyomaCharacter>(PlayerCharacter))
	{
		if (MyCharacter->WindowBase)
		{
			return MyCharacter->WindowBase;
		}
	}
	return nullptr;
}

void UWindowBase::ToggleMainMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("UWindowBase::ToggleMenu"));
	if (bIsMenuVisible && !bIsInventoryVisible )
	{
		UE_LOG(LogTemp, Warning, TEXT("UWindowBase::ToggleMenu : HideMenu"));
		OnRyomaStatus.Broadcast(CloseMainMenu);
		HideMenu();
	}
	else if ((!bIsMenuVisible && !bIsInventoryVisible) )
	{
		UE_LOG(LogTemp, Warning, TEXT("UWindowBase::ToggleMenu : DisplayMenu"));
		OnRyomaStatus.Broadcast(OpenMainMenu);
		DisplayMenu();
	}
}


void UWindowBase::HideInventory()
{

	if (bIsInventoryVisible && !bIsMenuVisible)
	{
		UE_LOG(LogTemp, Warning, TEXT("UWindowBase::Hide ture"));
		MainMenu_UMG->SetVisibility(ESlateVisibility::Visible);
		InventoryWindow->SetVisibility(ESlateVisibility::Collapsed);
		bIsInventoryVisible = false;
		bIsMenuVisible = true;
	}

	if (bIsMenuVisible)
	{
		UE_LOG(LogTemp, Warning, TEXT("HideInventory::bIsMenuVisible ture"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HideInventory::bIsMenuVisible false"));
	}
	

}

void UWindowBase::ShowInventory()
{
	
	if (!bIsInventoryVisible)
	{
		MainMenu_UMG->SetVisibility(ESlateVisibility::Collapsed);
		InventoryWindow->SetVisibility(ESlateVisibility::Visible);
		bIsInventoryVisible = true;
		bIsMenuVisible = false;
	}
	

	
}
void UWindowBase::DisplayMenu()
{
	if (MainMenu_UMG && !bIsShopMenuVisible)
	{
		bIsMenuVisible = true;
		MainMenu_UMG->SetVisibility(ESlateVisibility::Visible);
		const FInputModeGameAndUI InputMode;
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.0001f);
		GetWorld()->GetFirstPlayerController()->SetInputMode(InputMode);
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	}
}

void UWindowBase::HideMenu()
{
	if (MainMenu_UMG && !bIsShopMenuVisible)
	{
		bIsMenuVisible = false;
		MainMenu_UMG->SetVisibility(ESlateVisibility::Collapsed);
		const FInputModeGameOnly InputMode;
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
		GetWorld()->GetFirstPlayerController()->SetInputMode(InputMode);
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	
	}
}
