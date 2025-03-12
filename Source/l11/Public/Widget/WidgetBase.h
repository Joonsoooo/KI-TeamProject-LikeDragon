// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBase.generated.h"
class UPawnUIComponent;

/**
 * 
 */
class URyomaUIComponent;

UCLASS()
class L11_API UWidgetBase : public UUserWidget
{
	GENERATED_BODY()

	
//	virtual void SetTextLocation(FVector2d Location , UTextBlock* Text);
	
	 // 텍스트 , 이미지 , 가져오는 
	/*
	 
	 
	  WIDGET BASE DUMMY - CPP / BP 연결 베이스 / 헬프 펑션 (텍스트 정도 , 사이즈 . 내용변경도 하는 함수 , 유효성 체크해주는 함수 , )

	  ㄴMAINMENU (MANAGER WIDGET BASE ) 위젯들을 담고 추가하고 삭제하고 (스택구조  , 인덱스 변경도 필요함 , 최초 실행 시 데이터 불러오기)
	  ㄴ 진짜 매니징만 , 로더 (창을 불러오는) , 운영만 한다 
		

	
	나중에 필요하면 함수 구현
	*/

protected:
	virtual void NativeOnInitialized() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnOwingEnemyUIComponentInitialized(UEnemyUIComponent* EnemyUIComponent);
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnOwningRyomaUIComponentInitialized(URyomaUIComponent* HeroUIComponent);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnOwningPawnUIComponentInitialized(UPawnUIComponent* PawnUIComponent);
	
public:
	UFUNCTION(BlueprintCallable)
	void InitEnemyCreateWidget(AActor* EnemyActor);
	
   	TArray<UWidgetBase*> Children;
    	
    virtual bool WidgetValid(UWidget* Widget);
    virtual void FindHideWidget(FName FindWidgetName);
    	
};
