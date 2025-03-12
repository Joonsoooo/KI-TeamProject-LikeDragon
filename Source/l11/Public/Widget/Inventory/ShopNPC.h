// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Items/ItemInterface/InteractionInterface.h"
#include "UObject/Object.h"
#include "ShopNPC.generated.h"



class UItemBase;
/**
 * 
 */
UCLASS()
class L11_API AShopNPC : public ACharacter , public IInteractionInterface
{
	GENERATED_BODY()

 public:
//
 	AShopNPC();
	void InitializedSellItem(const TSubclassOf<UItemBase> BaseClass , const int32 InQuantity );
	
	UFUNCTION()
	void SetSellItemReference(UItemBase* ShopItemData );
	FORCEINLINE UItemBase* GetItemData() const { return SellItemReference; }
	UPROPERTY(EditAnywhere , Category = Widgets)
	
	TSubclassOf<class UShopMainMenu> BP_ShopMainMenu;
	
	UPROPERTY()
	class UShopMainMenu* ShopMainMenu;
	
	void OpenShopMainMenu(ARyomaCharacter* character);

	UFUNCTION(BlueprintCallable)
	void QuietShopMainMenu();
	
protected:
	virtual void BeginPlay() override;
	virtual void Interact(ARyomaCharacter* PlayerCharacter) override;
	void PurchaseItem(const ARyomaCharacter* Taker);
	void UpdateInteractableData();
	
	UPROPERTY(EditInstanceOnly, Category="SellItem | Item Initialization")
	UDataTable* SellItemDataTable;
	
	UPROPERTY(EditInstanceOnly, Category="SellItem | Item Initialization")
	FName DesiredSellItemID;
		
	UPROPERTY(EditInstanceOnly, Category="SellItem | Item Reference")
	UItemBase* SellItemReference;
	
	UPROPERTY(EditInstanceOnly, Category="SellItem | Quantity")
	int32 SellItemQuantity;

	UPROPERTY(EditInstanceOnly, Category="SellItem | Item Initialization")
	UTexture2D* SellItemTexture;
	
	UPROPERTY(VisibleInstanceOnly, Category="SellItem | Interaction")
	FInteractableData SellInstanceInteractableData;

	UPROPERTY()
	ARyomaCharacter* RyomaPlayerCharacter;

	bool bIsShopMainMenuState = false;



	
};
