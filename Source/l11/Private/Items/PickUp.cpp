// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PickUp.h"

#include "Components/Inventory/InventoryComponent.h"
#include "Items/ItemBase.h"
#include "Engine/DataTable.h"
#include "Widget/Inventory/PickUpItem.h"
#include "Blueprint/UserWidget.h"
#include "Controllers/Players/RyomaController.h"

APickUp::APickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
}

void APickUp::BeginPlay()
{
	Super::BeginPlay();
	InitializedPickUp(UItemBase::StaticClass() , ItemQuantity);


	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	ARyomaController* RyomaPlayerController = Cast<ARyomaController>(PlayerController);
	if (BP_PickUpItem)
	{
		PickUpItemClass = CreateWidget<UPickUpItem>(RyomaPlayerController , BP_PickUpItem);
		if (PickUpItemClass)
		{
			PickUpItemClass->AddToViewport();
			PickUpItemClass->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void APickUp::InitializedPickUp(const TSubclassOf<UItemBase> BaseClass, const int32 InQuantity)
{
	if (ItemDataTable && !DesiredItemID.IsNone())
	{
		
		const FItemData* ItemData = ItemDataTable->FindRow<FItemData>(DesiredItemID , DesiredItemID.ToString());
		ItemReference = NewObject<UItemBase>(this , BaseClass);
		ItemReference->ItemID = ItemData->ItemID;
		ItemReference->ItemType = ItemData->ItemType;
		ItemReference->ItemQuality = ItemData->ItemQuality; 
		ItemReference->ItemTextData = ItemData->ItemTextData;
		ItemReference->ItemAssetData = ItemData->ItemAssetData;
		ItemReference->ItemStatus = ItemData->ItemStatus;

		InQuantity <= 0 ? ItemReference->SetQuantity(1) : ItemReference->SetQuantity(InQuantity);
		
		UpdateInteractableData();
		
	}
}

void APickUp::InitializeDrop(UItemBase* ItemToDrop, const int32 InQuantity)
{
	ItemReference = ItemToDrop;
	InQuantity <= 0 ? ItemReference->SetQuantity(1) : ItemReference->SetQuantity(InQuantity);

	UpdateInteractableData();
}

void APickUp::UpdateInteractableData()
{
	InstanceInteractableData.InteractionType = EInteractionType::Pickup;
	InstanceInteractableData.Action = ItemReference->ItemTextData.InteractionText;
	InstanceInteractableData.Name = ItemReference->ItemTextData.Name;
	InstanceInteractableData.Quality = ItemReference->ItemQuality;
	InstanceInteractableData.Image = ItemReference->ItemAssetData.Icon;
	InteractableData = InstanceInteractableData;
	
	
}

void APickUp::Interact(ARyomaCharacter* PlayerCharacter)
{
	if (PlayerCharacter)
	{
		PickUpItem(PlayerCharacter);
	}
}

void APickUp::PickUpItem(const ARyomaCharacter* Taker)
{
	if (!IsPendingKillPending())
	{
		if (ItemReference)
		{
			if (UInventoryComponent* PlayerInventory = Taker->GetInventory())
			{
				const FAddItemResult AddItemResult = PlayerInventory->HandleAddItem(ItemReference);
				switch (AddItemResult.AddResult)
				{
				case EAddItem::NoItemAdd:
					break;
					
				case EAddItem::AddItem:
					UpdateInteractableData();
					Taker->UpdateInteractionWidget();
					break;
					
				case EAddItem::AllItems:
					PickUpItemClass->SetPickUpItemData(ItemReference);
					if (PickUpItemClass->OnPickUpItemAnim.IsBound())
					{
						UE_LOG(LogTemp, Warning, TEXT("OnPickUpItemAnim::bind"));
						PickUpItemClass->OnPickUpItemAnim.Broadcast();
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("OnPickUpItemAnim.unbind"));
					}
					Destroy();
					break;
					
				}
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

