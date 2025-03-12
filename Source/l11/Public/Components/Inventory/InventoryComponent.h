// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnInventoryUpdate);

class UItemBase;

UENUM(BlueprintType)
enum class EAddItem : uint8
{
	NoItemAdd UMETA(DisplayName = "NoItemAdd"),
	AddItem UMETA(DisplayName = "Item"),
	AllItems UMETA(DisplayName = "AllItems"),
};

USTRUCT(BlueprintType)
struct FAddItemResult
{
	GENERATED_BODY()

	FAddItemResult() : Amount(0) , AddResult(EAddItem::NoItemAdd)  , ResultText(FText::GetEmpty())
	{};

	UPROPERTY(BlueprintReadOnly , Category = "Add Item")
	int32 Amount;
	UPROPERTY(BlueprintReadOnly , Category = "Add Item")
	EAddItem AddResult;
	UPROPERTY(BlueprintReadOnly , Category = "Add Item")
	FText ResultText;

	static FAddItemResult AddedNone(const FText& ErrorText)
	{
		FAddItemResult AddedNoneResult;
		AddedNoneResult.Amount = 0;
		AddedNoneResult.AddResult = EAddItem::NoItemAdd;
		AddedNoneResult.ResultText = ErrorText;
		return AddedNoneResult;
	};
	static FAddItemResult AddedItem(const int32 AddedAmount , const FText& ErrorText)
	{
		FAddItemResult AddedItemResult;
		AddedItemResult.Amount = AddedAmount;
		AddedItemResult.AddResult = EAddItem::AddItem;
		AddedItemResult.ResultText = ErrorText;
		return AddedItemResult;
	};
	static FAddItemResult AddedAllItem(const int32 AddedAmount , const FText& Message)
	{
		FAddItemResult AddedAllItemResult;
		AddedAllItemResult.Amount = AddedAmount;
		AddedAllItemResult.AddResult = EAddItem::AllItems;
		AddedAllItemResult.ResultText = Message;
		return AddedAllItemResult;
	};
	
};


UCLASS( ClassGroup =(Custom) , meta=(BlueprintSpawnableComponent) )
class L11_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	
	UFUNCTION(Category = "Inventory")
	FAddItemResult HandleAddItem(UItemBase* InputItem);
	UFUNCTION(Category = "Inventory")
	UItemBase* FindMatchingItem(UItemBase* ItemIn) const;
	UFUNCTION(Category = "Inventory")
	UItemBase* FindNextItemByID(UItemBase* ItemIn) const;
	UFUNCTION(Category = "Inventory")
	UItemBase* FindNextPartialStack(UItemBase* ItemIn) const;

	UFUNCTION(Category = "Inventory")
	void RemoveSingleInstanceOfItem(UItemBase* RemoveItem);
	
	UFUNCTION(Category = "Inventory")
	int32 RemoveAmountOfItem(UItemBase* ItemIn , int32 DesiredAmountRemove);
	UFUNCTION(Category = "Inventory")
	void SplitExistingStack(UItemBase* ItemIn , const int32 AmountToSplit);


	//---------Get-------------
	UFUNCTION(Category = "Inventory")
	 int32 GetSlotsCapacity()const {return InventorySlotCapacity;};
	UFUNCTION(Category = "Inventory")
	 TArray<UItemBase*>  GetInventoryContents() const {return InventoryContents;};
	
	//--------Set-------------
	UFUNCTION(Category = "Inventory")
	 void SetSlotCapacity(const int32 NewSlotCapacity) {InventorySlotCapacity = NewSlotCapacity;};
	void SetInventoryContents(int32 UseItemindex);

	
	//---------------------------
	FOnInventoryUpdate OnInventoryUpdate;

	
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	int32 InventorySlotCapacity;
	
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<TObjectPtr<UItemBase>> InventoryContents;
	
	virtual void BeginPlay() override;
	
	FAddItemResult HandleNoneStackableItems(UItemBase* InputItem , int32 RequestAddAmount);
	int32 HandleStackableItems(UItemBase* ItemIn, int32 RequestAddAmount);
	int32 CalulateNumberFullStack(UItemBase* StackableItem , int32 InitialRequestAddAmount);

	void AddNewItem(UItemBase* Item , const int32 AmountToAdd);

	int32 NullIndex = 0;
	bool bIsUseItem = false;
};
