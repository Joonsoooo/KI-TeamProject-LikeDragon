// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WindowBase.h"
#include "PickUpItem.generated.h"
class UItemBase;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPickUpItemAnim);

class UTextBlock;
/**
 * 
 */
UCLASS()
class L11_API UPickUpItem : public UWindowBase
{
	GENERATED_BODY()

	public:

	void SetPickUpItemData(const UItemBase* PickUpData);

	UPROPERTY(BlueprintAssignable)
	FOnPickUpItemAnim OnPickUpItemAnim;
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget) , Category = "PickUpItem")
	UTextBlock* NameText;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget) , Category = "PickUpItem")
	UImage* PickUpImage;
	
	
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget) , Category = "PickUpItem")
	UImage* Star;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget) , Category = "PickUpItem")
	UImage* Star_1;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget) , Category = "PickUpItem")
	UImage* Star_2;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget) , Category = "PickUpItem")
	UImage* Star_3;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget) , Category = "PickUpItem")
	UImage* Star_4;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget) , Category = "PickUpItem")
	UImage* Star_5;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget) , Category = "PickUpItem")
	UImage* Star_6;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget) , Category = "PickUpItem")
	UImage* Star_7;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget) , Category = "PickUpItem")
	UImage* Star_8;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget) , Category = "PickUpItem")
	UImage* Star_9;
	
	
	void ChangedStarImage(int8 Quality);

	UFUNCTION(BlueprintCallable, Category = "PickUpItem")
	void ClearSlotItemQuality();

	virtual void NativeConstruct() override;




	private:

	TArray<UImage*> StarImages;
};
