// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/PickUpItem.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Items/ItemBase.h"

void UPickUpItem::NativeConstruct()
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
	
}


void UPickUpItem::SetPickUpItemData(const UItemBase* PickUpData)
{
	switch (PickUpData->ItemQuality)
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

	NameText->SetText(PickUpData->ItemTextData.Name);
	PickUpImage->SetBrushFromTexture(PickUpData->ItemAssetData.Icon);
}

void UPickUpItem::ChangedStarImage(int8 Quality)
{
	for (int i = 0; i < Quality; i++)
	{
		StarImages[i]->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UPickUpItem::ClearSlotItemQuality()
{
	for (int i = 0; i < 10; i++)
	{
		StarImages[i]->SetVisibility(ESlateVisibility::Visible);
	}
}

