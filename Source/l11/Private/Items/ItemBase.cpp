// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemBase.h"
#include "Items/ItemData/ItemDataStructs.h"
#include "Components/Inventory/InventoryComponent.h"

UItemBase::UItemBase() : bIsCopy(false) , bIsPickUp(false)
{
	
}

void UItemBase::ResetItemFlags() 
{
	bIsCopy = false;
	bIsPickUp = false;
}

//
UItemBase* UItemBase::CreateItemCopy() const
{
	UItemBase* ItemCopy = NewObject<UItemBase>(StaticClass());

	ItemCopy->ItemID = this->ItemID;
	ItemCopy->ItemType = this->ItemType;
	ItemCopy->ItemStatus = this->ItemStatus;
	ItemCopy->ItemQuantity = this->ItemQuantity;
	ItemCopy->ItemQuality = this->ItemQuality;
	ItemCopy->ItemAssetData = this->ItemAssetData;
	ItemCopy->ItemTextData = this->ItemTextData;
	ItemCopy->bIsPickUp = true;
	
	
	return ItemCopy;
}

void UItemBase::SetQuantity(const int32 NewQuantity)
{
	if (NewQuantity != Quantity)
	{
		Quantity = FMath::Clamp(NewQuantity, 0, ItemQuantity.bIsMaxQuantity ? ItemQuantity.MaxQuantity : 10);

		if (OwningInventory)
		{
			if (Quantity <= 0)
			{
				OwningInventory->RemoveSingleInstanceOfItem(this);
			}
		
		}

	}
	
}

void UItemBase::UseItem(ARyomaCharacter* PlayerCharacter)
{
}
