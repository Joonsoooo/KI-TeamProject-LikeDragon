// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/InventoryItemSlot.h"

#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "AbilitySystem/BaseAttributeSet.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/UniformGridPanel.h"
#include "Components/WrapBox.h"
#include "Controllers/Players/RyomaController.h"
#include "Items/ItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/ShopMainMenu.h"
#include "Widget/Inventory/InventoryPanel.h"
#include "Widget/Inventory/InventoryWindow.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include <WinSock2.h>
#include "Windows/HideWindowsPlatformTypes.h"
#include "Widget/Inventory/ItemClickWindow.h"
#include "Widget/Inventory/MainMenu_UMG.h"
#include "Widget/Inventory/ShopNPC.h"

void UInventoryItemSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
}

void UInventoryItemSlot::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (ItemReference)
	{
		ItemIcon->SetBrushFromTexture(ItemReference->ItemAssetData.Icon);
	}



	SlotButton->OnClicked.AddDynamic(this , &UInventoryItemSlot::SetClick);
	SlotButton->OnHovered.AddDynamic(this , &UInventoryItemSlot::SlotHovered);
	SlotButton->OnUnhovered.AddDynamic(this , &UInventoryItemSlot::SlotUnHovered);

	if (BP_ItemClickWindow)
	{
		ItemClickWindow = CreateWidget<UItemClickWindow>(this , BP_ItemClickWindow);
		if (ItemClickWindow)
		{
			ItemClickWindow->AddToViewport(10);
			ItemClickWindow->SetVisibility(ESlateVisibility::Hidden);
			ItemClickWindow->YesButton->OnClicked.AddDynamic(this , &UInventoryItemSlot::UseSlotItem);
			
		}
	}
	
}

void UInventoryItemSlot::SetClick()
{
	ItemClickWindow->SetVisibility(ESlateVisibility::Visible);
	const FInputModeUIOnly InputMode;
	GetWorld()->GetFirstPlayerController()->SetInputMode(InputMode);

}

void UInventoryItemSlot::SlotHovered()
{
	ACharacter* PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetCharacter();
	if (ARyomaCharacter* MyCharacter = Cast<ARyomaCharacter>(PlayerCharacter))
	{
		if (MyCharacter->WindowBase)
		{
			UInventoryWindow* FindInventoryWindow = MyCharacter->WindowBase->InventoryWindow;
			if (FindInventoryWindow)
			{
				UE_LOG(LogTemp, Warning, TEXT("Successfully accessed InventoryWindow through WindowBase."));
				FindInventoryWindow->OnItemHovered.Broadcast(ItemReference);
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Click on item %s") , *GetName());
	
}

void UInventoryItemSlot::SlotUnHovered()
{
	UInventoryWindow* FindInventoryWindow =GetWindowBaseWidget()->InventoryWindow;
	if (FindInventoryWindow)
	{
		UE_LOG(LogTemp, Warning, TEXT("Successfully accessed InventoryWindow through WindowBase."));
		FindInventoryWindow->OnItemUnhovered.Broadcast();
	}
}

void UInventoryItemSlot::ItemSlotHidden()
{
		SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		SetRenderOpacity(0);
}

void UInventoryItemSlot::SetUpdateIcon(UItemBase* UpdateItem)
{
	ItemIcon->SetBrushFromTexture(UpdateItem->ItemAssetData.Icon);
}

void UInventoryItemSlot::UseSlotItem()
{
	const FInputModeGameAndUI InputMode;
	GetWorld()->GetFirstPlayerController()->SetInputMode(InputMode);
	
	ItemClickWindow->SetVisibility(ESlateVisibility::Hidden);
	ARyomaCharacter* RyomaCharacter = GetWindowBaseWidget()->InventoryWindow->InventoryPanel->PlayerCharacter;

	if (UBaseAbilitySystemComponent* ASC = RyomaCharacter->GetBaseAbilitySystemComponent())
	{
		float HealthRecovery = ItemReference->ItemStatus.RestorationAmount;
		UE_LOG(LogTemp, Warning, TEXT("Health Recovery: %f"), HealthRecovery);

		float HealthCurrentValue = ASC->GetNumericAttribute(UBaseAttributeSet::GetHealthCurrentAttribute());

		float NewHealthValue = HealthCurrentValue + HealthRecovery;

		ASC->SetNumericAttributeBase(UBaseAttributeSet::GetHealthCurrentAttribute(), NewHealthValue);

		UE_LOG(LogTemp, Warning, TEXT("Health updated: %f -> %f"), HealthCurrentValue, NewHealthValue);

	}

	GetWindowBaseWidget()->InventoryWindow->InventoryPanel->OnRemoveItemIndex.Broadcast(FName(GetName()) , ItemReference);
}

