// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Interaction/InteractionWidget.h"




void UInteractionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	
}

void UInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();


}

void UInteractionWidget::UpdateWidget(const FInteractableData* UpdateInteractableData) const
{
	
	
	switch (UpdateInteractableData->InteractionType)
	{
		
	case EInteractionType::Pickup:
	
		break;
	case EInteractionType::NonePlayerCharacter:
		break;
	case EInteractionType::Device:
		break;
	case EInteractionType::Toggle:
		break;
	case EInteractionType::Container:
		break;
	}
	
	
	
}

