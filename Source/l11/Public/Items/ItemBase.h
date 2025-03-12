// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Players/RyomaCharacter.h"
#include "Items/ItemData/ItemDataStructs.h"
#include "ItemBase.generated.h"

class UInventoryComponent;

/**
 * 
 */

//정찬희
//게임 아이템 정보 설정
UCLASS()
class L11_API UItemBase : public UObject
{
	GENERATED_BODY()

public:
	
	UPROPERTY()
	UInventoryComponent* OwningInventory;
	
	UPROPERTY(VisibleAnywhere , category = "Item")
	FName ItemID;
	
	UPROPERTY(VisibleAnywhere,  Category = "Item" )
	int32 Quantity;
	
	UPROPERTY(VisibleAnywhere , category = "Item")
	EItemType ItemType;

	UPROPERTY(VisibleAnywhere , category = "Item")
	EItemQuality ItemQuality;

	UPROPERTY(VisibleAnywhere , category = "Item")
	FItemStatus ItemStatus;

	UPROPERTY(VisibleAnywhere , category = "Item")
	FItemTextData ItemTextData;

	UPROPERTY(VisibleAnywhere , category = "Item")
	FItemNumericData ItemNumericData;
	
	UPROPERTY(VisibleAnywhere , category = "Item")
	FItemQuantity ItemQuantity;
	
	UPROPERTY(VisibleAnywhere , category = "Item")
	FItemAssetData ItemAssetData;

	bool bIsCopy;
	bool bIsPickUp;
	
	//정찬희
	//생성자
	UItemBase();

	void ResetItemFlags();
	//아이템의 정보를 복사 후 리턴 
	UItemBase* CreateItemCopy() const;

	FORCEINLINE bool IsFullItemStack() const { return Quantity == ItemNumericData.MaxStackSize; }

	
	//아이템 개수 설정
	void SetQuantity(const int32 NewQuantity);

	//아이템 사용 관련 가상함수 , 자식 클래스에서 재정의 예정
	virtual void UseItem(ARyomaCharacter* PlayerCharacter);
	

	
	
protected:

	// 인벤토리 아이템 bool operator== 는 연산자 재정의하여 bool 값을 반환
	bool operator==(const FName& OtherID) const
	{
		//OtherID 와 ItemID 가 같다면 트루 반환
		return this->ItemID == OtherID;
	}
};
