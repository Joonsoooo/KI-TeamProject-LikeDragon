// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/PawnUIInterface.h"

URyomaUIComponent* IPawnUIInterface::GetRyomaUIComponent() const
{
	return nullptr;
}

// Add default functionality here for any IPawnUIInterface functions that are not pure virtual.
UEnemyUIComponent* IPawnUIInterface::GetEnemyUIComponent() const
{
	return nullptr;
}
