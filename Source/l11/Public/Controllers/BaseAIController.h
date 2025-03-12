// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "BaseAIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
struct FAIStimulus;
/**
 * 
 */
UCLASS()
class L11_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABaseAIController(const FObjectInitializer& ObjectInitializer);

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAISenseConfig_Sight* AISenseConfig_Sight;

	UFUNCTION()
	virtual void OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	bool bDetourCrowdAvoidence = true;

	UPROPERTY(EditDefaultsOnly, Category = "AI", meta = (EditCondition = "bDetourCrowdAvoidence", UIMin = "1", UIMax = "4"))
	int32 DetourCrowdAvoidenceQuality = 4;

	UPROPERTY(EditDefaultsOnly, Category = "AI", meta = (EditCondition = "bDetourCrowdAvoidence"))
	float CollisionQueryRange = 600.0f;
};
