// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStates/DefaultGameState.h"

// void ADefaultGameState::SetDefaultsGameState(EDefaultsGameState OutDefaultsGameState)
// {
// 	DefaultsGameState = OutDefaultsGameState;
//
// 	if (OnChangeDefaultsGameState.IsBound())
// 	{
// 		OnChangeDefaultsGameState.Broadcast();
// 	}
// }
//
// void ADefaultGameState::SetCombatGameState(ECombatGameState OutCombatGameState)
// {
// 	CombatGameState = OutCombatGameState;
//
// 	if (OnChangeCombatGameState.IsBound())
// 	{
// 		OnChangeCombatGameState.Broadcast();
// 	}
// }

void ADefaultGameState::SetDefaultsGameState(EDefaultsGameState OutDefaultGameState)
{
	DefaultsGameState = OutDefaultGameState;
	
	if (SetDefaultsGameStateChanged.IsBound())
	{
		SetDefaultsGameStateChanged.Broadcast(OutDefaultGameState);
	}
}

void ADefaultGameState::SetCombatGameState(ECombatGameState OutCombatGameState)
{
	CombatGameState = OutCombatGameState;

	if (SetCombatGameStateChanged.IsBound())
	{
		SetCombatGameStateChanged.Broadcast(OutCombatGameState);
	}
}

EDefaultsGameState ADefaultGameState::GetDefaultsGameState()
{
	if (GetDefaultsGameStateChanged.IsBound())
	{
		GetDefaultsGameStateChanged.Broadcast();
	}
	
	return DefaultsGameState;
}

ECombatGameState ADefaultGameState::GetCombatGameState()
{
	if (GetCombatGameStateChanged.IsBound())
	{
		GetCombatGameStateChanged.Broadcast();
	}
	
	return CombatGameState;
}
