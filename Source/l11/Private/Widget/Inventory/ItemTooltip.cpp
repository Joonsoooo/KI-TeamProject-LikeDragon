// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/ItemTooltip.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Widget/Inventory/InventoryItemSlot.h"



void UItemTooltip::NativeConstruct()
{
	Super::NativeConstruct();
	
	StarImages.Add(Star);
	StarImages.Add(Star_1);
	StarImages.Add(Star_2);
	StarImages.Add(Star_3);
	StarImages.Add(Star_4);
	StarImages.Add(Star_5);
	StarImages.Add(Star_6);
	StarImages.Add(Star_7);
	StarImages.Add(Star_8);
	StarImages.Add(Star_9);
	TooltipImage->SetOpacity(0);
}

void UItemTooltip::SetTextAndIcon(UItemBase* ItemSlotData)
{
	UE_LOG(LogTemp, Warning, TEXT("SendSlotItemData"));
	if (ItemSlotData)
	{
		ItemName->SetText(ItemSlotData->ItemTextData.Name);
		Description->SetText(ItemSlotData->ItemTextData.Description);
		TooltipImage->SetBrushFromTexture(ItemSlotData->ItemAssetData.Icon);
		TooltipImage->SetOpacity(1);
		SlotItemQuality(ItemSlotData->ItemQuality);
	}
}

void UItemTooltip::SlotItemQuality(EItemQuality Quality)
{
	switch (Quality)
	{
	case EItemQuality::OneStar:
		ChangedStarImage(1);
		break;
	case EItemQuality::TwoStar:
		ChangedStarImage(2);
		break;
	case EItemQuality::ThreeStar:
		ChangedStarImage(3);
		break;
	case EItemQuality::FourStar:
		ChangedStarImage(4);
		break;
	case EItemQuality::FiveStar:
		ChangedStarImage(5);
		break;
	case EItemQuality::SixStar:
		ChangedStarImage(6);
		break;
	case EItemQuality::SevenStar:
		ChangedStarImage(7);
		break;
	case EItemQuality::EightStar:
		ChangedStarImage(8);
		break;
	case EItemQuality::NineStar:
		ChangedStarImage(9);
		break;
	case EItemQuality::TenStar:
		ChangedStarImage(10);
		break;
	}
}

void UItemTooltip::ChangedStarImage(int8 Quality)
{
	for (int i = 0; i < Quality; i++)
	{
		StarImages[i]->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UItemTooltip::ClearTooltip()
{
	for (int i = 0; i < 10; i++)
	{
		StarImages[i]->SetVisibility(ESlateVisibility::Visible);
	}
	ItemName->SetText(FText::FromString(""));
	Description->SetText(FText::FromString(""));
	TooltipImage->SetOpacity(0);
}
