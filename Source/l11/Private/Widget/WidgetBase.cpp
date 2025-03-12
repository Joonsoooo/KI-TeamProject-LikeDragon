// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/WidgetBase.h"
#include "Blueprint/WidgetTree.h"
#include "Components/UI/PawnUIComponent.h"
#include "Interfaces/PawnUIInterface.h"

void UWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn()))
	{
		if (UPawnUIComponent* PawnUIComponent = PawnUIInterface->GetPawnUIComponent())
		{
			BP_OnOwningPawnUIComponentInitialized((PawnUIComponent));
		}
		
		if (URyomaUIComponent* RyomaUIComponent = PawnUIInterface->GetRyomaUIComponent())
		{
			BP_OnOwningRyomaUIComponentInitialized(RyomaUIComponent);
		}
	}
}

void UWidgetBase::InitEnemyCreateWidget(AActor* EnemyActor)
{
	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(EnemyActor))
	{
		if (UEnemyUIComponent* EnemyUIComponent = PawnUIInterface->GetEnemyUIComponent())
		{
			BP_OnOwingEnemyUIComponentInitialized(EnemyUIComponent);
		}
	}
}


bool UWidgetBase::WidgetValid(UWidget* Widget)
{
	if (IsValid(Widget))
	{
		return true;
	}
	else
	{
		return false;
	}
	
}


void UWidgetBase::FindHideWidget(FName FindWidgetName)
{
	WidgetTree->ForEachWidget([this , FindWidgetName](UWidget* Widget)
{
	if (FindWidgetName == Widget->GetName())
	{
		Widget->SetVisibility(ESlateVisibility::Hidden);
		UE_LOG(LogTemp , Warning , TEXT("FindWidget : %s ") , *Widget->GetName());
	}
});
}

