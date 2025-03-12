// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStates/BaseGameState.h"
#include "DefaultGameState.generated.h"

// DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChangeDefaultsGameState);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChangeCombatGameState);

UENUM(BlueprintType)
enum class EDefaultsGameState : uint8
{
	Exploration = 0 UMETA(DisplayName = "Exploration"), // 탐험 모드, NPC와 상호 작용 가능, 플레이어는 전투 불가, 
	Sequence UMETA(DisplayName = "Sequence"),
	Combat UMETA(DisplayName = "Combat"), // 플레이어 특정 입력 불가 , 시퀀스 NPC 제외 이동 불가
	NPCInteraction UMETA(DisplayName = "NPCInteraction"), //전투 불가 (특정 스테이트 때 적이 플레이어 인식 불가?), 플레이어 특정 입력 불가
										
};

UENUM(BlueprintType)
enum class ECombatGameState : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	PlayerDetection UMETA(DisplayName = "Player Detection"), // 플레이어 발견
	BattouKatana UMETA(DisplayName = "BattouKatana"),  // 플레이어 발견 후 적이 칼을 뽑음
	ChasePlayer UMETA(DisplayName = "ChasePlayer"), // 플레이어를 쫓아옴 
	BattleStateStart UMETA(DisplayName = "BattleStateStart"), // 전투 시퀀스 발동
	BattleStart UMETA(DisplayName = "BattleStart"), // 전투 시퀀스 끝나고 전투 시작 
	BattleEnd UMETA(DisplayName = "BattleEnd"), // 마지막 적 처치 시 전투 끝
	BattleStateEnd UMETA(DisplayName = "BattleStateEnd"), // 전투 후 UI 확인 버튼 누르면 전투 상황 끝
	RyomaDeath UMETA(DisplayName = "RyomaDeath"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetDefaultsGameStateChanged, EDefaultsGameState, OutDefaultGameState); // Set할 때
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetCombatGameStateChanged, ECombatGameState, OutCombatGameState); 
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGetCombatGameStateChanged); // Get 할 때
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGetDefaultsGameStateChanged);

/**
 * 
 */
UCLASS()
class L11_API ADefaultGameState : public ABaseGameState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	EDefaultsGameState DefaultsGameState;

	UPROPERTY(BlueprintReadWrite)
	ECombatGameState CombatGameState;

	UPROPERTY(BlueprintAssignable)
	FGetCombatGameStateChanged GetDefaultsGameStateChanged;

	UPROPERTY(BlueprintAssignable)
	FGetDefaultsGameStateChanged GetCombatGameStateChanged;

	UPROPERTY(BlueprintAssignable)
	FSetDefaultsGameStateChanged SetDefaultsGameStateChanged;

	UPROPERTY(BlueprintAssignable)
	FSetCombatGameStateChanged SetCombatGameStateChanged;

	UFUNCTION(BlueprintCallable)
	void SetDefaultsGameState(EDefaultsGameState OutDefaultGameState);
	UFUNCTION(BlueprintCallable)
	void SetCombatGameState(ECombatGameState OutCombatGameState);

	UFUNCTION(BlueprintCallable)
	EDefaultsGameState GetDefaultsGameState();
	UFUNCTION(BlueprintCallable)
	ECombatGameState GetCombatGameState();

public:
	UPROPERTY()
	int32 DetectedCombatEnemy = 0;
	
// private:
// 	UPROPERTY()
// 	EDefaultsGameState DefaultsGameState;
// 	UPROPERTY()
// 	ECombatGameState CombatGameState;
// 	
// public:
// 	FOnChangeDefaultsGameState OnChangeDefaultsGameState;
// 	FOnChangeCombatGameState OnChangeCombatGameState;
	
public:
	// // 이준수 Getter DefaultsGameState
	// UFUNCTION(BlueprintCallable, Category = "GameState")
	// EDefaultsGameState GetDefaultsGameState() { return DefaultsGameState; }
	// // 이준수 Getter CombatGameState
	// UFUNCTION(BlueprintCallable, Category = "GameState")
	// ECombatGameState GetCombatGameState() { return CombatGameState;}
	//
	// // 이준수 Setter DefaultsGameState
	// UFUNCTION(BlueprintCallable, Category = "GameState")
	// void SetDefaultsGameState(EDefaultsGameState OutDefaultsGameState);
	// // 이준수 Setter CombatGameState
	// UFUNCTION(BlueprintCallable, Category = "GameState")
	// void SetCombatGameState(ECombatGameState OutCombatGameState);
};
