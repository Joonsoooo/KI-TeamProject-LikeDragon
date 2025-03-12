// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemInterface/InteractionInterface.h"
#include "Characters/Players/RyomaCharacter.h"

void IInteractionInterface::BeginFocus()
{
}

void IInteractionInterface::EndFocus()
{
}

// Add default functionality here for any IInteractionInterface functions that are not pure virtual.
void IInteractionInterface::BeginInteract()
{
}

void IInteractionInterface::EndInteract()
{
}

void IInteractionInterface::Interact(ARyomaCharacter* PlayerCharacter)
{
}
