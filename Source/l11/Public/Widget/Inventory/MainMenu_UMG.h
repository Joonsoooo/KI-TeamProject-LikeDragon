// Fill out your copyright notice in the Description page of Project Settings.

/*
메인 메뉴에 관련된 창의 스택을 관리
MainMenu_UMG 창의 이벤트 등 기능을 관리

---Window Base와--------
MainMenu_UMG가 생성 시 모든 MainMenu 연관 위젯들을 생성하고 배열에 저장
WindowBase에서 Show , Hide , Remove , Add 가 필요하다고 요창하면
맞는 함수 실행
인덱스 변경하는 함수


*/
#pragma once

#include "CoreMinimal.h"
#include "Widget/WindowBase.h"
#include "MainMenu_UMG.generated.h"


/**
 * 
 */

class UInventoryPanel;
DECLARE_MULTICAST_DELEGATE(FOnButtonDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryWindow , EClickButton , button);
class UWindowBase;
class ARyomaCharacter;

UCLASS()
class L11_API UMainMenu_UMG : public UWindowBase
{
	GENERATED_BODY()

public:
	
	
//--------------버튼 바인딩
	UPROPERTY(Meta = (BindWidget))
	class UButton* Back;
	//
	// UPROPERTY(Meta = (BindWidget))
	// class UButton* Map;
	//
	UPROPERTY(Meta = (BindWidget))
	class UButton* Select;
	//
	UPROPERTY(Meta = (BindWidget))
	class UButton* MainMenu_Equipment;
	//
	UPROPERTY(Meta = (BindWidget))
	class UButton* MainMenu_Inventory;
	//
	UPROPERTY(Meta = (BindWidget))
	class UButton* MainMenu_Status;
//----------------------------------------------------
	FOnButtonDelegate OnClickButton;
	FOnInventoryWindow OnInventoryWindow;
//----------위젯-----------------------------
	
	
//-------------------------------	
	UPROPERTY()
	UInventoryPanel* PreInventoryPanel;

	UFUNCTION(BlueprintCallable)
	UButton* GetHoveredButton() {return HoveredButton; };

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;


private:
	
	UPROPERTY()
	ARyomaCharacter* PlayerCharacter;

protected:
	
	//void FindHideWidgets(FName FindWidgetName);
	void FindShowWidgets(FName FindWidgetName);
	
	UFUNCTION(BlueprintCallable)
	void OpenInventoryMenu();

	UFUNCTION(BlueprintCallable)
	void QuitMainMenu();

	UFUNCTION()
	void StatusHovered();
	UFUNCTION()
	void InventoryHovered();
	UFUNCTION()
	void EquipementHovered();

	UPROPERTY()
	UButton* HoveredButton;
	
	
	
	void SetHoveredButton( UButton* button ) {HoveredButton = button; };
};


