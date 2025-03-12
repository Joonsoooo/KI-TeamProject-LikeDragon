		// Fill out your copyright notice in the Description page of Project Settings.
/*

 1. MainMenu_UMG가 실행되면 데이터 (아이템 인벤토리 정보)로드
 2. 자식 위젯들을 생성하고 정보를 전달
 3. 


ㄴWINDOW BASE (WIDGET BASE)- 데이터 리딩, 최우선 구현은 아님 하면 좋을 정도(버튼의 호버나 클릭 슬롯들은 만들고 지우는 기능을 넣얻주고)
, 갱신까지 처리 ,이름도 생각 , 창에서 실행되는 라이프 사이클 , 생성 소멸 관리 , 버튼이벤트 등
	창에서 관리하는 것을 담고 있어야함, MC 패턴 , 기능만 구현 , 업데이트 
필요한 함수
MainMenu_UMG에 생성된 위젯의 정보를 보내는 함수
버튼 이벤트 시 상황에 맞는 함수
아이템 사용 시


---WindowBase는 위젯 간 상호작용이나 데이터에 관한 거

---위젯의 Show , Hide는 MainMenu_UMG와----------
자식 위젯에서 Visibility와 관련된 버튼을 누른 경우 MainMenu_UMG에 Hide , Show 여부를 전달
자식 위젯에서 위젯의 삭제나 생성과 관련된 버튼을 누른경우 MainMenu_UMG에 해당 위젯의 정보와 , Add OR Delete 여부를 전달




---정보 관련 함수들은 WindowBase와 자식 간---------
데이터를 가지고 오고 저장한다 (인벤토리 어떤 인베토리 슬롯에 아이템이 들어있는지 , 돈 , 아이템의 정보 등 )
정보 업데이트 (아이템의 삭제 및 추가)
---------------------



하위 위젯
1. 버튼 이벤트 시 WindowBase에 전달
2. 각 맞는 기능 구현
3. 아이템의 정보를 가져오고 아이템을 사용하면 WindowBase에 해당 정보를 전달


	 
	  -INVENTORYWINDOW(WINDOW BASE TYPE) V -> 인벤토리는 소지품 , 농작물 등 다른 위젯들이 있음
받은 정보를 인벤토리에 업데이트


	  
-STATUSWINDOW(WINDOW BASE TYPE) V 1개
	  -EQUIPMENTWINDOW(WINDOW BASE TYPE) V 1개
 
실제 에디터에서 보여지는 창에서 사용할 기능을 구현
버튼 호버가 될 경우 데이터 로딩 , 윈도우창을 띄우고(자식에서 구현?) , 


 */

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemInterface/InteractionInterface.h"
#include "Items/ItemData/ItemDataStructs.h"
#include "Widget/WidgetBase.h"
#include "WindowBase.generated.h"

class AShopNPC;

UENUM(BlueprintType)
enum EClickButton
{
	OpenInventory UMETA(DisplayName = "Open Inventory"),
	CloseInventory UMETA(DisplayName = "Close Inventory"),
	OpenMainMenu UMETA(DisplayName = "Open Main Menu"),
	CloseMainMenu UMETA(DisplayName = "Close MainMenu"),
	OpenShopMainMenu UMETA(DisplayName = "Open Shop Main Menu"),
	CloseShopMenu UMETA(DisplayName = "Close Shop Menu"),
	
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWindowState , EClickButton , ButtonState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShopWindowVisible , bool , State);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRyomaStatus , EClickButton , ButtonState);


struct FInteractableData;
class UButton;
class UImage;
class UDataTable;
/**
 * 
 */
UCLASS()
class L11_API UWindowBase : public UWidgetBase , public IInteractionInterface
{
	GENERATED_BODY()

	protected:
	
	virtual void NativeConstruct() override;
	
//------------- 데이터 테이블-----------------
	public:
	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	UDataTable* ItemDataTable;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	FName ItemID;
	
	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	EItemType ItemType;
	
	UPROPERTY(EditAnywhere ,BlueprintReadWrite )
	EItemQuality ItemQuality;

	UPROPERTY(EditAnywhere ,BlueprintReadWrite)
	FItemStatus ItemStatus;

	UPROPERTY(EditAnywhere ,BlueprintReadWrite)
	FItemTextData ItemTextData;

	UPROPERTY(EditAnywhere ,BlueprintReadWrite)
	FItemAssetData ItemAssetData;
	
	UPROPERTY(EditAnywhere ,BlueprintReadWrite)
	FItemQuantity ItemQuantity;
	
//------------- 위젯-----------------

	
	UPROPERTY(EditAnywhere , Category = Widgets)
	TSubclassOf<class UMainMenu_UMG> BP_MainMenu_UMG;
	
	UPROPERTY()
	class UMainMenu_UMG* MainMenu_UMG;
	

	UPROPERTY(EditAnywhere , Category = Widgets)
	TSubclassOf<class UInventoryWindow> BP_InventoryWindow;

	UPROPERTY()
	class UInventoryWindow* InventoryWindow;
	
	UPROPERTY(EditAnywhere , Category = Widgets)
	TSubclassOf<class UInteractionWidget> BP_InteractionWidget;
	UPROPERTY()
	class UInteractionWidget* InteractionWidget;

	void MainWindowsSelect();
	void MainWindowsESC();
	
	
	void UpdateInteractionWidget(const FInteractableData* CurrentInteractableData) const;

	FOnShopWindowVisible OnShopWindowVisible;
	FOnWindowState OnWindowState;
	UPROPERTY(BlueprintAssignable, Category = "RyomaStatus")
	FOnRyomaStatus OnRyomaStatus;
	void ShowInteractionWidget();
	void HideInteractionWidget();

	UFUNCTION()
	void ToggleMainMenu();

	UFUNCTION(BlueprintCallable)
	UWindowBase* GetWindowBaseWidget();
	
//-------------함수-------------
protected:

	ARyomaCharacter* PlayerRyomaCharacter;
	UFUNCTION(BlueprintCallable)
	void DisplayMenu();
	
	UFUNCTION(BlueprintCallable)
	void HideMenu();
	
	UFUNCTION(BlueprintCallable)
	void ShowInventory();

	UFUNCTION(BlueprintCallable)
	void HideInventory();
	
	UFUNCTION()
	void ShopMenuVisible(bool ShopWindowState);
	
	UFUNCTION(BlueprintCallable)
	virtual void SetWidgetVisibility(EClickButton ButtonState);

	UFUNCTION(BlueprintCallable)
	bool GetbIsInventoryVisible() {return bIsInventoryVisible;};

	AShopNPC* ShopNPC;
	
//-------------변수-----------
	
	

	TArray<UWindowBase*> WidgetArray;
	
	bool bIsInventoryVisible = false;
	bool bIsMenuVisible = false;
	bool bIsShopMenuVisible = false;
};






