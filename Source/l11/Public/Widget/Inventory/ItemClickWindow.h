// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WindowBase.h"
#include "ItemClickWindow.generated.h"

/**
 * 
 */
UCLASS()
class L11_API UItemClickWindow : public UWindowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UButton* YesButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* NoButton;

protected:

	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void HideClickWindow();
	
};
