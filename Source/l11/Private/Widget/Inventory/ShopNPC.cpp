// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/ShopNPC.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/UniformGridPanel.h"
#include "Components/Inventory/InventoryComponent.h"
#include "Widget/ShopMainMenu.h"
#include "Items/ItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/WidgetBase.h"
#include "Widget/Inventory/InventoryPanel.h"
#include "Widget/Inventory/InventoryWindow.h"

AShopNPC::AShopNPC()
{
	PrimaryActorTick.bCanEverTick = false;



}
void AShopNPC::BeginPlay()
{
	Super::BeginPlay();
	InitializedSellItem(UItemBase::StaticClass() , SellItemQuantity);

	if (BP_ShopMainMenu)
	{
		UE_LOG(LogTemp, Warning, TEXT("BP_ShopMainMenu"));
		ShopMainMenu = CreateWidget<UShopMainMenu>(GetWorld() ,BP_ShopMainMenu);
		if (ShopMainMenu)
		{
			UE_LOG(LogTemp, Warning, TEXT("Shop Main Menu"));
			ShopMainMenu->AddToViewport(5);
			ShopMainMenu->SetVisibility(ESlateVisibility::Hidden);
			ShopMainMenu->OnPurchaseItem.BindDynamic(this, &AShopNPC::SetSellItemReference);
			ShopMainMenu->Back->OnClicked.AddDynamic(this , &AShopNPC::QuietShopMainMenu);
		}
	}
	
	
}

void AShopNPC::Interact(ARyomaCharacter* PlayerCharacter)
{
	
	if (PlayerCharacter)
	{
		RyomaPlayerCharacter = Cast<ARyomaCharacter>(PlayerCharacter);
		OpenShopMainMenu(RyomaPlayerCharacter);
	}
}

void AShopNPC::PurchaseItem(const ARyomaCharacter* Taker)
{
	if (!IsPendingKillPending())
	{
		if (SellItemReference)
		{
			if (UInventoryComponent* PlayerInventory = Taker->GetInventory())
			{
				const FAddItemResult AddItemResult = PlayerInventory->HandleAddItem(SellItemReference);
				UE_LOG(LogTemp, Warning, TEXT("%s ")  , *AddItemResult.ResultText.ToString());
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Player Inventor Null")); 
			}
			
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Pickup internal Item referance was Somehow Null")); 
		}
	}
}

void AShopNPC::InitializedSellItem(const TSubclassOf<UItemBase> BaseClass, const int32 InQuantity)
{
	if (SellItemDataTable && !DesiredSellItemID.IsNone())
	{
		
		const FItemData* ItemData = SellItemDataTable->FindRow<FItemData>(DesiredSellItemID , DesiredSellItemID.ToString());
		SellItemReference = NewObject<UItemBase>(this , BaseClass);
		SellItemReference->ItemID = ItemData->ItemID;
		SellItemReference->ItemType = ItemData->ItemType;
		SellItemReference->ItemQuality = ItemData->ItemQuality; 
		SellItemReference->ItemTextData = ItemData->ItemTextData;
		SellItemReference->ItemAssetData = ItemData->ItemAssetData;
		SellItemReference->ItemStatus = ItemData->ItemStatus;

		InQuantity <= 0 ? SellItemReference->SetQuantity(1) : SellItemReference->SetQuantity(InQuantity);
		
		UpdateInteractableData();
		
	}
}

void AShopNPC::SetSellItemReference(UItemBase* ShopItemData)
{
	SellItemReference = ShopItemData;
	if (SellItemReference && RyomaPlayerCharacter)
	{
		PurchaseItem(RyomaPlayerCharacter);
	}

	
}

void AShopNPC::UpdateInteractableData()
{
	SellInstanceInteractableData.InteractionType = EInteractionType::NonePlayerCharacter;
	SellInstanceInteractableData.Action = SellItemReference->ItemTextData.InteractionText;
	SellInstanceInteractableData.Name = SellItemReference->ItemTextData.Name;
	SellInstanceInteractableData.Quality = SellItemReference->ItemQuality;
	SellInstanceInteractableData.Image = SellItemReference->ItemAssetData.Icon;
	InteractableData = SellInstanceInteractableData;
}

void AShopNPC::OpenShopMainMenu(ARyomaCharacter* character)
{
	UE_LOG(LogTemp, Warning, TEXT("UWindowBase::ToggleShopMainMenu"));
	if (!bIsShopMainMenuState)
	{
		character->WindowBase->OnShopWindowVisible.Broadcast(true);
		bIsShopMainMenuState = true;
		ShopMainMenu->SetVisibility(ESlateVisibility::Visible);
		
		
	}
}

void AShopNPC::QuietShopMainMenu()
{
	RyomaPlayerCharacter->WindowBase->OnShopWindowVisible.Broadcast(false);
	bIsShopMainMenuState = false;
	ShopMainMenu->SetVisibility(ESlateVisibility::Hidden);
	
}


