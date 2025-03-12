// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Inventory/InventoryComponent.h"

#include "Items/ItemBase.h"


UItemBase* UInventoryComponent::FindMatchingItem(UItemBase* ItemIn) const
{
	if (ItemIn)
	{
		if (InventoryContents.Contains(ItemIn))
		{
			return ItemIn;
		}
	}
	return nullptr;
}

UItemBase* UInventoryComponent::FindNextItemByID(UItemBase* ItemIn) const
{
	if (ItemIn)
	{
		if (const TArray<TObjectPtr<UItemBase>>::ElementType* Result = InventoryContents.FindByKey(ItemIn))
		{
			return *Result;
		}
	}
	return nullptr;
}

UItemBase* UInventoryComponent::FindNextPartialStack(UItemBase* ItemIn) const
{
	if (const TArray<TObjectPtr<UItemBase>>::ElementType* Result = InventoryContents.FindByPredicate([&ItemIn](const UItemBase* InventoryItem)
	{
		return InventoryItem->ItemID == ItemIn->ItemID && !InventoryItem->IsFullItemStack();
	}))
	{
		return *Result;	
	}
	return nullptr;
}

int32 UInventoryComponent::CalulateNumberFullStack(UItemBase* StackableItem, int32 InitialRequestAddAmount)
{
	const int32 AddAmountMakeFullStack = StackableItem->ItemNumericData.MaxStackSize - StackableItem->Quantity;
	return FMath::Min(InitialRequestAddAmount, AddAmountMakeFullStack);
}

void UInventoryComponent::RemoveSingleInstanceOfItem(UItemBase* RemoveItem)
{
	InventoryContents.RemoveSingle(RemoveItem);
	OnInventoryUpdate.Broadcast();
}

int32 UInventoryComponent::RemoveAmountOfItem(UItemBase* ItemIn, int32 DesiredAmountRemove)
{
	const int32 RemoveItemAmount = FMath::Min(DesiredAmountRemove, ItemIn->Quantity);
	ItemIn->SetQuantity(ItemIn->Quantity - RemoveItemAmount);

	OnInventoryUpdate.Broadcast();
	return RemoveItemAmount;
}



void UInventoryComponent::SplitExistingStack(UItemBase* ItemIn, const int32 AmountToSplit)
{
	if (!(InventoryContents.Num() + 1 >  InventorySlotCapacity))
	{
		
		RemoveAmountOfItem(ItemIn, AmountToSplit);
		AddNewItem(ItemIn , AmountToSplit);
		
	}
}

void UInventoryComponent::SetInventoryContents(int32 UseItemindex)
{
	NullIndex = UseItemindex;
	bIsUseItem = true;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

FAddItemResult UInventoryComponent::HandleNoneStackableItems(UItemBase* InputItem, int32 RequestAddAmount)
{
	// Adding Item Overflow Slot Capacity
	if (InventoryContents.Num() + 1 > InventorySlotCapacity)
	{
		return FAddItemResult::AddedNone(FText::Format(FText::FromString("Could Not add {0} to the Inventory . All Inventory Slots are Full") , InputItem->ItemTextData.Name));
	}

	AddNewItem(InputItem, 1);
	return FAddItemResult::AddedAllItem(RequestAddAmount , FText::Format(FText::FromString("Successfully add single {0} to the Inventory") , InputItem->ItemTextData.Name));

}

int32 UInventoryComponent::HandleStackableItems(UItemBase* ItemIn, int32 RequestAddAmount)
{
	
	return 0;
}


FAddItemResult UInventoryComponent::HandleAddItem(UItemBase* InputItem)
{
	if (GetOwner())
	{
		const int32 InitialRequestAddAmount = InputItem->Quantity;
		//Handle Non Stackable Items
		if (!InputItem->ItemNumericData.bIsStackable)
		{
			
			return HandleNoneStackableItems(InputItem , InitialRequestAddAmount);
		}
		else
		{
			UE_LOG(LogTemp , Error , TEXT("bIsStackable is true "))
		}
		
		//Handle Add Stackable Items
		const int32 StackableAmountAdded = HandleStackableItems(InputItem, InitialRequestAddAmount);

		if (StackableAmountAdded == InitialRequestAddAmount)
		{
			FAddItemResult::AddedAllItem( InitialRequestAddAmount ,FText::Format(
				FText::FromString("Successfuly added {0} {1} to the Inventory") ,
				InitialRequestAddAmount , InputItem->ItemTextData.Name ));
			UE_LOG(LogTemp , Error , TEXT("AddedAllItem "))
		}
		if (StackableAmountAdded < InitialRequestAddAmount && StackableAmountAdded > 0)
		{
			
			FAddItemResult::AddedItem(InitialRequestAddAmount , FText::Format(
				FText::FromString("Partial Amount of {0} Added to the Inventory , Number added = {1}") ,
				InputItem->ItemTextData.Name  , StackableAmountAdded));
			UE_LOG(LogTemp , Error , TEXT("AddedItem "))
		}
		
		if (StackableAmountAdded <= 0)
		{
			FAddItemResult::AddedNone(FText::Format(
		FText::FromString("Couldn't add {0} to the Inventory , no remaining Inventory slot or Invalid item") ,
		InputItem->ItemTextData.Name  , StackableAmountAdded));
			UE_LOG(LogTemp , Error , TEXT("AddedNone "))
		}
	
	}

	check(false);
	return FAddItemResult::AddedNone(FText::FromString("Trt Add item fallthrough error. GetOwner() check somehow failed."));
}


void UInventoryComponent::AddNewItem(UItemBase* Item, const int32 AmountToAdd)
{
	UItemBase* NewItem;


	// if the Item already a copy, or is World PickUp 
	if (Item->bIsCopy || Item->bIsPickUp)
	{
		NewItem = Item;
		NewItem->ResetItemFlags();
	}
	else
	{
		//used when splitting or dragging to from another inventorySlot
		NewItem = Item->CreateItemCopy();
	}

	NewItem->OwningInventory = this;
	NewItem->SetQuantity(AmountToAdd);

	if (bIsUseItem)
	{
		bIsUseItem = false;
		InventoryContents[NullIndex] = NewItem;
	}
	else
	{
		InventoryContents.Add(NewItem);
	}
	
	OnInventoryUpdate.Broadcast();
	
}
