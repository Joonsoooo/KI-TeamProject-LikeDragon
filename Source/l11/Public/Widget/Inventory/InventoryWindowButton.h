// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/Inventory/InventoryWindow.h"
#include "InventoryWindowButton.generated.h"

/**
 * 
 */
UCLASS()
class L11_API UInventoryWindowButton : public UInventoryWindow
{
	GENERATED_BODY()

	public:
	UPROPERTY(meta = (BindWidget))
	UButton* InventoryBack;
	
	UPROPERTY(meta = (BindWidget))
	UButton* InventoryUse;


	protected:
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void CloseInventoryWindow();
};
