// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "EnemyCharacter.generated.h"

class UEnemyCombatComponent;
class UEnemyUIComponent;
class UWidgetComponent;
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGetCurrentBossHealth); // Get 할 때


UCLASS()
class L11_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	AEnemyCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UEnemyCombatComponent* EnemyCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UEnemyUIComponent* EnemyUIComponent;

	UPROPERTY(visibleAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* WidgetComponent;

protected:
	virtual void PossessedBy(AController* NewController) override;

	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;

	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UEnemyUIComponent* GetEnemyUIComponent() const override;

	virtual void BeginPlay() override;
	
private:
	void InitEnemyStartUpData();

public:
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }

	UFUNCTION(BlueprintCallable)
	void GetCurrentBossHealth();

	UPROPERTY(BlueprintAssignable)
	FGetCurrentBossHealth GetCurrentedBossHealth;
private:
	
};
