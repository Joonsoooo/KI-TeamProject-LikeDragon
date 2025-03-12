// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ShopMainMenu.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Items/ItemBase.h"
#include "Engine/DataTable.h"
#include "Widget/Inventory/InventoryPanel.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include <WinSock2.h>
#include "Windows/HideWindowsPlatformTypes.h"

class UUniformGridPanel;

void UShopMainMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitializeItems(UItemBase::StaticClass() , SellItemQuantity);

	SellItemIDs.Add(DesiredItemID_001);
	SellItemIDs.Add(DesiredItemID_002);
	SellItemIDs.Add(DesiredItemID_003);
	SellItemIDs.Add(DesiredItemID_004);
	SellItemIDs.Add(DesiredItemID_005);
	SellItemIDs.Add(DesiredItemID_006);

	SellItemNameArray.Add(SellItem1Name);
	SellItemNameArray.Add(SellItem2Name);
	SellItemNameArray.Add(SellItem3Name);
	SellItemNameArray.Add(SellItem4Name);
	SellItemNameArray.Add(SellItem5Name);
	SellItemNameArray.Add(SellItem6Name);

	FoodIconArray.Add(FoodIcon1);
	FoodIconArray.Add(FoodIcon2);
	FoodIconArray.Add(FoodIcon3);
	FoodIconArray.Add(FoodIcon4);
	FoodIconArray.Add(FoodIcon5);
	FoodIconArray.Add(FoodIcon6);

	TooltipImage->SetOpacity(0);
	WidgetTree->ForEachWidget([this] (UWidget* widget)
	{
		if (FName("ShopInventory") == widget->GetName())
		{
			ShopInventoryPanel = Cast<UInventoryPanel>(widget);
		}
		
	});
	
}

void UShopMainMenu::NativeConstruct()
{
	Super::NativeConstruct();


	InitializeItems(UItemBase::StaticClass() , SellItemQuantity);
	SellFoodMenuData();
	
	SellItem1->OnHovered.AddDynamic(this , &UShopMainMenu::SetSellItem1Tooltip);
	SellItem2->OnHovered.AddDynamic(this , &UShopMainMenu::SetSellItem2Tooltip);
	SellItem3->OnHovered.AddDynamic(this , &UShopMainMenu::SetSellItem3Tooltip);
	SellItem4->OnHovered.AddDynamic(this , &UShopMainMenu::SetSellItem4Tooltip);
	SellItem5->OnHovered.AddDynamic(this , &UShopMainMenu::SetSellItem5Tooltip);
	SellItem6->OnHovered.AddDynamic(this , &UShopMainMenu::SetSellItem6Tooltip);

	SellItem1->OnUnhovered.AddDynamic(this , &UShopMainMenu::SellItemUnHovered);
	SellItem2->OnUnhovered.AddDynamic(this , &UShopMainMenu::SellItemUnHovered);
	SellItem3->OnUnhovered.AddDynamic(this , &UShopMainMenu::SellItemUnHovered);
	SellItem4->OnUnhovered.AddDynamic(this , &UShopMainMenu::SellItemUnHovered);
	SellItem5->OnUnhovered.AddDynamic(this , &UShopMainMenu::SellItemUnHovered);
	SellItem6->OnUnhovered.AddDynamic(this , &UShopMainMenu::SellItemUnHovered);
	
	SellItem1->OnClicked.AddDynamic(this , &UShopMainMenu::OpenSellWindow);
	SellItem2->OnClicked.AddDynamic(this , &UShopMainMenu::OpenSellWindow);
	SellItem3->OnClicked.AddDynamic(this , &UShopMainMenu::OpenSellWindow);
	SellItem4->OnClicked.AddDynamic(this , &UShopMainMenu::OpenSellWindow);
	SellItem5->OnClicked.AddDynamic(this , &UShopMainMenu::OpenSellWindow);
	SellItem6->OnClicked.AddDynamic(this , &UShopMainMenu::OpenSellWindow);

	ShopYesButton->OnClicked.AddDynamic(this , &UShopMainMenu::ShopYesButtonClick);
	ShopNoButton->OnClicked.AddDynamic(this , &UShopMainMenu::ShopNoButtonClick);

	//Select->OnClicked.AddDynamic(this , &UShopMainMenu::Select);
	
	FoodItemArray.Add(SellItem1);
	FoodItemArray.Add(SellItem2);
	FoodItemArray.Add(SellItem3);
	FoodItemArray.Add(SellItem4);
	FoodItemArray.Add(SellItem5);
	FoodItemArray.Add(SellItem6);
	
}

void UShopMainMenu::InitializeItems(const TSubclassOf<UItemBase> BaseClass ,  int32 Quantity)
{
	
	
	for (int i = 0; i < SellItemIDs.Num(); i++)
	{
		if (SellItemDataTable && !SellItemReferenceArray.IsValidIndex(i) )
		{
			const FItemData* ItemData = ItemDataTable->FindRow<FItemData>(SellItemIDs[i] ,SellItemIDs[i].ToString());
			ItemReference = NewObject<UItemBase>(this , BaseClass);
			if (ItemReference)
			{
				
				UE_LOG(LogTemp, Error, TEXT(" Created to find item data!"));
				ItemReference->ItemID = ItemData->ItemID;
				ItemReference->ItemType = ItemData->ItemType;
				ItemReference->ItemQuality = ItemData->ItemQuality; 
				ItemReference->ItemTextData = ItemData->ItemTextData;
				ItemReference->ItemAssetData = ItemData->ItemAssetData;
				ItemReference->ItemStatus = ItemData->ItemStatus;
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT(" Failed to find item data!"));
			}
			Quantity <= 0 ? ItemReference->SetQuantity(1) : ItemReference->SetQuantity(Quantity);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT(" IsValidIndex Failed!"));
		}
		SellItemReferenceArray.Add(ItemReference);
	}
}

void UShopMainMenu::SellFoodMenuData()
{
	for (int i = 0; i < SellItemIDs.Num(); i++)
	{
		SellItemNameArray[i]->SetText(SellItemReferenceArray[i]->ItemTextData.Name);
		FoodIconArray[i]->SetBrushFromTexture(SellItemReferenceArray[i]->ItemAssetData.Icon);
	}
}


void UShopMainMenu::SetSellItem1Tooltip()
{
	TooltipImage->SetOpacity(1);
	TooltipImage->SetBrushFromTexture(SellItemReferenceArray[0]->ItemAssetData.Icon);
	ItemName->SetText(SellItemReferenceArray[0]->ItemTextData.Name);
	DescriptionTextLine(0);
	SetPurchaseItemReference(0);
	
}

void UShopMainMenu::SetSellItem2Tooltip()
{
	TooltipImage->SetOpacity(1);
	TooltipImage->SetBrushFromTexture(SellItemReferenceArray[1]->ItemAssetData.Icon);
	ItemName->SetText(SellItemReferenceArray[1]->ItemTextData.Name);
	DescriptionTextLine(1);
	SetPurchaseItemReference(1);
}

void UShopMainMenu::SetSellItem3Tooltip()
{
	TooltipImage->SetOpacity(1);
	TooltipImage->SetBrushFromTexture(SellItemReferenceArray[2]->ItemAssetData.Icon);
	ItemName->SetText(SellItemReferenceArray[2]->ItemTextData.Name);
	DescriptionTextLine(2);
	SetPurchaseItemReference(2);
}

void UShopMainMenu::SetSellItem4Tooltip()
{
	TooltipImage->SetOpacity(1);
	TooltipImage->SetBrushFromTexture(SellItemReferenceArray[3]->ItemAssetData.Icon);
	ItemName->SetText(SellItemReferenceArray[3]->ItemTextData.Name);
	DescriptionTextLine(3);
	SetPurchaseItemReference(3);
}

void UShopMainMenu::SetSellItem5Tooltip()
{
	TooltipImage->SetOpacity(1);
	TooltipImage->SetBrushFromTexture(SellItemReferenceArray[4]->ItemAssetData.Icon);
	ItemName->SetText(SellItemReferenceArray[4]->ItemTextData.Name);
	DescriptionTextLine(4);
	SetPurchaseItemReference(4);
}

void UShopMainMenu::SetSellItem6Tooltip()
{
	TooltipImage->SetOpacity(1);
	TooltipImage->SetBrushFromTexture(SellItemReferenceArray[5]->ItemAssetData.Icon);
	ItemName->SetText(SellItemReferenceArray[5]->ItemTextData.Name);
	DescriptionTextLine(5);
	SetPurchaseItemReference(5);
}

void UShopMainMenu::SellItemUnHovered()
{
	TooltipImage->SetOpacity(0);
	ItemName->SetText(FText::FromString(""));
	Description->SetText(FText::FromString(""));
}

void UShopMainMenu::OpenSellWindow()
{
	FindHideWidget(FName("FoodTooltipWindow"));
	ShowFindWidget(FName("SellItemWindow"));
	SetMouseButtonClicked();
	UE_LOG(LogTemp, Error, TEXT(" Button Clicked!"));
}

void UShopMainMenu::ShopNoButtonClick()
{
	FindHideWidget(FName("SellItemWindow"));
	ShowFindWidget(FName("FoodTooltipWindow"));
	SetMouseButtonClicked();
}

void UShopMainMenu::ShopYesButtonClick()
{
	FindHideWidget(FName("SellItemWindow"));
	ShowFindWidget(FName("FoodTooltipWindow"));
	OnPurchaseItem.Execute(ItemReference);
	SetMouseButtonClicked();
	
}

void UShopMainMenu::SetPurchaseItemReference(int32 index)
{
	ItemReference = SellItemReferenceArray[index];
}

void UShopMainMenu::SetMouseButtonClicked()
{
	if (!bIsSellItemClicked)
	{
		bIsSellItemClicked= true;
		WidgetTree->ForEachWidget([this](UWidget* Widget)
	{
		if (Widget->GetName() == FName("VerticalBox_34"))
		{
			Widget->SetVisibility(ESlateVisibility::HitTestInvisible);
		}
	});
	}
	else
	{
		bIsSellItemClicked= false;
		WidgetTree->ForEachWidget([this](UWidget* Widget)
	{
		if (Widget->GetName() == FName("VerticalBox_34"))
		{
			Widget->SetVisibility(ESlateVisibility::Visible);
		}
	});
	}
	
}

void UShopMainMenu::DescriptionTextLine(int32 index)
{
	FString OriginalText = SellItemReferenceArray[index]->ItemTextData.Description.ToString();
	
	TArray<FString> Sentences;
	
	OriginalText.ParseIntoArray(Sentences, TEXT("."), true);
	
	FString ModifiedText = FString::Join(Sentences, TEXT(".\n"));
	
	Description->SetText(FText::FromString(ModifiedText));
}

void UShopMainMenu::ShowFindWidget(FName FindWidgetName)
{
	WidgetTree->ForEachWidget([this , FindWidgetName](UWidget* Widget)
{
if (FindWidgetName == Widget->GetName())
{
	Widget->SetVisibility(ESlateVisibility::Visible);
	UE_LOG(LogTemp , Warning , TEXT("FindWidget : %s ") , *Widget->GetName());
}
});
}
