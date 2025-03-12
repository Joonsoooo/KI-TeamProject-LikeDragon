// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/Players/RyomaController.h"
#include "Characters/Players/RyomaCharacter.h"


void ARyomaController::BeginPlay()
{
	Super::BeginPlay();

	ARyomaCharacter* RyomaCharacter = Cast<ARyomaCharacter>(GetPawn());
	// if (RyomaCharacter)
	// {
	// 	RyomaCharacter->InteractionStateDelegate.AddDynamic(this , &ARyomaController::InteractState);
	// }

	// if (BP_MainMenu_UMG)
	// {
	// 	MainMenu_UMG = CreateWidget<UWidgetBase>(this , BP_MainMenu_UMG);
	// 	if (MainMenu_UMG)
	// 	{
	// 		UE_LOG(LogTemp, Warning, TEXT("CreateWidget<UMainMenu_UMG> 생성!"));
	// 		MainMenu_UMG->AddToViewport();
	// 		MainMenu_UMG->SetVisibility(ESlateVisibility::Hidden);
	// 	}
	// 	else
	// 	{
	// 		UE_LOG(LogTemp, Warning, TEXT("CreateWidget<UMainMenu_UMG> 실패!"));
	// 	}
	// }	
	// else
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("BP_MainMenu_UMG가 nullptr 입니다. UMG 블루프린트가 할당되지 않았습니다."));
	// }

	//OnQuitButtonClicked.AddDynamic(this , &ARyomaController::HideMainMenu);

	
}

	


// void ARyomaController::InteractState(bool Interact)
// {
// 	ADefaultGameState* GameState = GetWorld()->GetGameState<ADefaultGameState>();
// 	if (GameState)
// 	{
// 		if (GameState->GetDefaultsGameState() == EDefaultsGameState::Exploration)
// 		{
// 			if (Interact)
// 			{
// 				ShowInteractWidget();
// 			}
// 			else
// 			{
// 				HideInteractWidget();
// 			}
// 		}
// 		else
// 		{
// 			HideInteractWidget();
// 		}
// 	}
// 	
// }
//
// void ARyomaController::ShowInteractWidget()
// {
// 	//위젯이 생성되지 않았을 때
// 	if (!InteractWidget)
// 	{
// 		InteractWidget = CreateWidget<UWidgetBase>(this, WBP_InteractWidget);
// 		if (InteractWidget)
// 		{
// 			InteractWidget->AddToViewport();
// 			UE_LOG(LogTemp, Warning, TEXT("ARyomaController::ShowInteractWidget"));
// 		}
// 		else
// 		{
// 			UE_LOG(LogTemp, Warning, TEXT("InteractWidget : null"));
// 		}
// 	}
// }
//
// void ARyomaController::HideInteractWidget()
// {
// 	//위젯이 지워지지 않았을 떄
// 	if (InteractWidget)
// 	{
// 		InteractWidget->RemoveFromParent();
// 		InteractWidget= nullptr;
//
// 		UE_LOG(LogTemp, Warning, TEXT("ARyomaController::HideInteractWidget"));
// 	}
//
// 	//위젯을 삭제
// }
//
// void ARyomaController::ToggleMainMenu()
// {
// 	UE_LOG(LogTemp, Warning, TEXT("InputAction"));
// 	
// 	if (!MainMenu_UMG) return;
// 	bIsShowMainMenu = !bIsShowMainMenu;
// 	
// 	if (bIsShowMainMenu)
// 	{
// 		ShowMainMenu();
// 	}
// 	else
// 	{
// 		HideMainMenu();
// 	}
// 	
// 	OnToggleMenDelegate.Broadcast(bIsShowMainMenu);
// }
//
// void ARyomaController::QuitMainMenu()
// {
// 	bIsShowMainMenu = false;
// 	bShowMouseCursor = false;
// 	bEnableClickEvents = false;
// 	bEnableMouseOverEvents = false;
// 	
// 	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
// 	SetInputMode(FInputModeGameOnly());
// 	MainMenu_UMG->SetVisibility(ESlateVisibility::Hidden);
// }
//
// void ARyomaController::ShowMainMenu()
// {
// 	UE_LOG(LogTemp, Warning, TEXT("Main Menu 열림"));
//
// 	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.0001f); // 시간은 멈추지만 입력은 활성화
//
// 	bShowMouseCursor = true;
// 	bEnableClickEvents = true;
// 	bEnableMouseOverEvents = true;
//
// 	FInputModeGameAndUI InputMode;
// 	InputMode.SetWidgetToFocus(MainMenu_UMG->TakeWidget());
// 	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
// 	SetInputMode(InputMode);
//
// 	MainMenu_UMG->SetVisibility(ESlateVisibility::Visible);
// }
//
//
// void ARyomaController::HideMainMenu()
// {
// 	bIsShowMainMenu = false;
// 	UE_LOG(LogTemp, Warning, TEXT("Main Menu 닫힘"));
// 		
// 	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
// 	SetInputMode(FInputModeGameOnly());
// 		
// 		
// 	bShowMouseCursor = false;
// 	bEnableClickEvents = false;
// 	bEnableMouseOverEvents = false;
// 	
// 	MainMenu_UMG->SetVisibility(ESlateVisibility::Hidden);
// }
//
//
// void ARyomaController::SetupInputComponent()
// {
// 	Super::SetupInputComponent();
//
// 	InputComponent->BindAction("ToggleMenu",IE_Pressed, this, &ARyomaController::ToggleMainMenu);
// }

ARyomaController::ARyomaController()
{
	RyomaTeamId = FGenericTeamId(0);
}

FGenericTeamId ARyomaController::GetGenericTeamId() const
{
	return RyomaTeamId;
}
