// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controllers/BasePlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "RyomaController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnToggleMenu, bool, bIsMenuVisible);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuitButtonClicked);
/**
 * 
 */
UCLASS()
class L11_API ARyomaController : public ABasePlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	// UFUNCTION()
	// void InteractState(bool Interact);
	//
	// void ShowInteractWidget();
	// void HideInteractWidget();
	//
	// UFUNCTION(BlueprintCallable)
	// void ToggleMainMenu();
	//
	// void QuitMainMenu();
	//
	// void ShowMainMenu();
	// UFUNCTION()
	// void HideMainMenu();
	//
	// UPROPERTY(meta=(BindWidget))
	// class UButton* Back;
	

public:
	// UPROPERTY(EditAnywhere)
	// TSubclassOf<class UWidgetBase> WBP_InteractWidget;
	//
	// UPROPERTY()
	// class UWidgetBase* InteractWidget;
	//
	// UPROPERTY(EditAnywhere)
	// TSubclassOf<class UWidgetBase> BP_MainMenu_UMG;
	//
	// UPROPERTY()
	// class UWidgetBase* MainMenu_UMG;

	//virtual void SetupInputComponent() override;	

	FOnToggleMenu OnToggleMenDelegate;
	//FOnQuitButtonClicked OnQuitButtonClicked;
	
	ARyomaController();
	virtual FGenericTeamId GetGenericTeamId() const override;

	

private:
	FGenericTeamId RyomaTeamId;

	//bool bIsShowMainMenu = false;
};
