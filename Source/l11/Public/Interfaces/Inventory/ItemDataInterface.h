// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemDataInterface.generated.h"

class UItemBase;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UItemDataInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class L11_API IItemDataInterface
{
	GENERATED_BODY()
	
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual UItemBase* GetSlotItemData(UItemBase* SlotItemData) = 0;

	

};
