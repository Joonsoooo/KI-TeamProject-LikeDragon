// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/UniformGridPanel.h"
#include "Widget/WindowBase.h"
#include "ShopMainMenu.generated.h"

class UInventoryPanel;
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnPurchaseItem, UItemBase*, PurchaseItemReference);

class UTextBlock;
class UItemBase;
/**
 * 
 */
UCLASS()
class L11_API UShopMainMenu : public UWindowBase
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditAnywhere, Category="SellItem | Item Initialization")
	UDataTable* SellItemDataTable;

	UPROPERTY(EditAnywhere, Category="SellItem | Item Initialization")
	FName DesiredItemID_001;

	UPROPERTY(EditAnywhere, Category="SellItem | Item Initialization")
	FName DesiredItemID_002;

	UPROPERTY(EditAnywhere, Category="SellItem | Item Initialization")
	FName DesiredItemID_003;

	UPROPERTY(EditAnywhere, Category="SellItem | Item Initialization")
	FName DesiredItemID_004;

	UPROPERTY(EditAnywhere, Category="SellItem | Item Initialization")
	FName DesiredItemID_005;

	UPROPERTY(EditAnywhere, Category="SellItem | Item Initialization")
	FName DesiredItemID_006;
	
	UPROPERTY(EditAnywhere, Category="SellItem | Item Reference")
	UItemBase* ItemReference;

	UPROPERTY(EditAnywhere, Category="SellItem | Quantity")
	int32 ItemQuantity_001;
	
	UPROPERTY(meta = (BindWidget))
	UButton* SellItem1;
	UPROPERTY(meta = (BindWidget))
	UButton* SellItem2;
	UPROPERTY(meta = (BindWidget))
	UButton* SellItem3;
	UPROPERTY(meta = (BindWidget))
	UButton* SellItem4;
	UPROPERTY(meta = (BindWidget))
	UButton* SellItem5;
	UPROPERTY(meta = (BindWidget))
	UButton* SellItem6;

	UPROPERTY(meta = (BindWidget))
	UImage* FoodIcon1;
	
	UPROPERTY(meta = (BindWidget))
	UImage* FoodIcon2;
	
	UPROPERTY(meta = (BindWidget))
	UImage* FoodIcon3;
	
	UPROPERTY(meta = (BindWidget))
	UImage* FoodIcon4;
	
	UPROPERTY(meta = (BindWidget))
	UImage* FoodIcon5;
	
	UPROPERTY(meta = (BindWidget))
	UImage* FoodIcon6;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SellItem1Name;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SellItem2Name;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SellItem3Name;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SellItem4Name;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SellItem5Name;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SellItem6Name;

	UPROPERTY(meta = (BindWidget))
	UImage* TooltipImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemName;

	UPROPERTY(meta = (BindWidget , MultiLine="true"))
	UTextBlock* Description;

	UPROPERTY(meta = (BindWidget))
	UButton* ShopYesButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ShopNoButton;

	UPROPERTY(meta = (BindWidget))
	UButton* Select;

	UPROPERTY(meta = (BindWidget))
	UButton* Back;

	FORCEINLINE UItemBase* GetSellItemReference() const {return SellItemReference;};

	FOnPurchaseItem OnPurchaseItem;
	
	UPROPERTY()
	UInventoryPanel* ShopInventoryPanel;

	UPROPERTY()
	TArray<UButton*> FoodItemArray;

	UFUNCTION()
	void OpenSellWindow();
	
protected:

	UPROPERTY()
	UItemBase* SellItemReference;
	
	int32 SellItemQuantity;

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	void InitializeItems(const TSubclassOf<UItemBase> BaseClass , int32 Quantity);
	UFUNCTION()
	void SellFoodMenuData();

	TArray<FName> SellItemIDs;
	
	TArray<UItemBase*> SellItemReferenceArray;

	TArray<UTextBlock*> SellItemNameArray;

	TArray<UImage*> FoodIconArray;
	

	void SetShopUniformGridPanel(UUniformGridPanel* UniformGridPanel);
	
	

	UFUNCTION()
	void SetSellItem1Tooltip();
	UFUNCTION()
	void SetSellItem2Tooltip();
	UFUNCTION()
	void SetSellItem3Tooltip();
	UFUNCTION()
	void SetSellItem4Tooltip();
	UFUNCTION()
	void SetSellItem5Tooltip();
	UFUNCTION()
	void SetSellItem6Tooltip();

	UFUNCTION()
	void SellItemUnHovered();
	
	void PlayShopButtonSound();

	void DescriptionTextLine(int32 index);

	UFUNCTION()
	void ShopYesButtonClick();
	UFUNCTION()
	void ShopNoButtonClick();

	void ShowFindWidget(FName FindWidgetName);

	void SetPurchaseItemReference(int32 index);
	void SetMouseButtonClicked();
	
	bool bIsSellItemClicked = false;
};


