// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemInterface/InteractionInterface.h"
#include "UObject/Object.h"
#include "PickUp.generated.h"

class UImage;
class UDataTable;
class UItemBase;

UCLASS()
class L11_API APickUp : public AActor , public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUp();
	void InitializedPickUp(const TSubclassOf<UItemBase> BaseClass , const int32 InQuantity );
	void InitializeDrop(UItemBase* ItemToDrop , const int32 InQuantity );
	FORCEINLINE UItemBase* GetItemData() const { return ItemReference; }

	UPROPERTY(EditAnywhere , Category = Widgets)
	TSubclassOf<class UPickUpItem> BP_PickUpItem;
	UPROPERTY()
	class UPickUpItem* PickUpItemClass;
	
protected:
	virtual void BeginPlay() override;
	virtual void Interact(ARyomaCharacter* PlayerCharacter) override;
	void PickUpItem(const ARyomaCharacter* Taker);
	
	void UpdateInteractableData();

	UPROPERTY(EditInstanceOnly, Category="PickUp | Item Initialization")
	UDataTable* ItemDataTable;
	
	UPROPERTY(EditInstanceOnly, Category="PickUp | Item Initialization")
	FName DesiredItemID;
		
	UPROPERTY(EditInstanceOnly, Category="PickUp | Item Reference")
	UItemBase* ItemReference;
	
	UPROPERTY(EditInstanceOnly, Category="PickUp | Quantity")
	int32 ItemQuantity;

	UPROPERTY(EditInstanceOnly, Category="PickUp | Item Initialization")
	UTexture2D* PickUpTexture;
	
	UPROPERTY(VisibleInstanceOnly, Category="PickUp | Interaction")
	FInteractableData InstanceInteractableData;

	

};

