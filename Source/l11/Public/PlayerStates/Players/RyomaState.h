// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerStates/BasePlayerState.h"
#include "RyomaState.generated.h"

UENUM(BlueprintType)
enum class ERunState : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Run UMETA(DisplayName = "Run"),
	Tired UMETA(DisplayName = "Tired"),
	Stop UMETA(DisplayName = "Stop"),
};

/**
 * 
 */
UCLASS()
class L11_API ARyomaState : public ABasePlayerState
{
	GENERATED_BODY()
	
private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	ERunState RunState = ERunState::None;

public:
	UFUNCTION(BlueprintCallable)
	void SetRunState(ERunState OutRunState) { RunState = OutRunState; }
	UFUNCTION(BlueprintCallable)
	ERunState GetRunState();
};
