// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "GameplayTagContainer.h"
#include "Characters/Enemies/EnemyCharacter.h"
#include "PlayerStates/Players/RyomaState.h"
#include "Items/ItemInterface/InteractionInterface.h" // 상호작용 인터페이스
#include "RyomaCharacter.generated.h"

class AShopNPC;
class UInventoryComponent;

DECLARE_MULTICAST_DELEGATE(FOnToggleMainMenu);
DECLARE_DELEGATE_OneParam(FRunStateDele, ERunState)
DECLARE_DELEGATE_OneParam(FTargetingDele, bool)
DECLARE_DELEGATE_OneParam(FSwayDele, bool)


//정찬희 , 상호작용 구조체 , 어떤 물체가 상호작용이 가능한지 체크한다. 라인트레이스에서 히트된 정보를 저장함
USTRUCT()
struct FInteractionData
{
	GENERATED_BODY()
	
	FInteractionData() : CurrentInteractable(nullptr)  , ShopNPC(nullptr), LastInteractionCheckTime(0.0f) {}

	//상호작용이 가능한 것인지 체크
	UPROPERTY()
	AActor* CurrentInteractable;

	UPROPERTY()
	AShopNPC* ShopNPC;
	
	UPROPERTY()
	float LastInteractionCheckTime;
};

#pragma region ForwardClass
class USpringArmComponent;
class UCameraComponent;
class UDataAsset_InputConfig;
class ARyomaState;
class ARyomaController;
class UCurveFloat;
class URyomaCombatComponent;
class UEnhancedInputLocalPlayerSubsystem;
class UInputAction;
class USphereComponent;
class AEnemyCharacter;
class URyomaUIComponent;
#pragma endregion ForwardClass

struct FInputActionValue;


/**
 *	
 */
UCLASS()
class L11_API ARyomaCharacter : public ABaseCharacter 
{
	GENERATED_BODY()
	
public:
	ARyomaCharacter();

private:
	virtual void BeginPlay() override;

#pragma region Components
private:
	UPROPERTY(EditAnywhere, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterInput", meta = (AllowPrivateAccess = true))
	UDataAsset_InputConfig* InputConfigDataAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RyomaState", meta = (AllowPrivateAccess = true))
	ARyomaState* RyomaState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RyomaController", meta = (AllowPrivateAccess = true))
	ARyomaController* RyomaController;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	URyomaCombatComponent* RyomaCombatComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "input", meta = (AllowPrivateAccess = "true"))
	UEnhancedInputLocalPlayerSubsystem* Subsystem;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input", meta = (AllowPrivateAccess = "true"))
	// FVector2D MovementVector;

	//이준수, 료마 UI 변수
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	URyomaUIComponent* RyomaUIComponent;

#pragma endregion Components

	
protected:
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;
	
	// 이준수, PawnCombatInterface에서 정의한 함수 오버라이드 
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	
	//이준수, 폰UI컴포넌트 가져오기 
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	//이준수, 료마UI컴포넌트 가져오기
	virtual URyomaUIComponent* GetRyomaUIComponent() const override;

#pragma region Input	
	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
	void Input_Run();
	void Input_PressedWalk();
	void Input_ReleasedWalk();

	void Input_AbilityInputPressed(FGameplayTag InputTag);
	void Input_AbilityInputReleased(FGameplayTag InputTag);
#pragma endregion Input

	//변수 영역
public:
	// 
	FRunStateDele RunState;
	FSwayDele Sway;
	FTargetingDele Targeting;
	
private:
	// 이준수, 달리기 타이머 
	FTimerHandle RunTimerHandle;

	// 달리기 시간 
	float StartTime = 0.0f;
	float EndTime = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", meta = (AllowPrivateAccess = "true"))
	bool IsTargeting;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", meta = (AllowPrivateAccess = "true"))
	bool IsSway;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Angle", meta = (AllowPrivateAccess = "true"))
	FVector SwayDirection = FVector(0.f, 0.f ,0.f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Angle", meta = (AllowPrivateAccess = "true"))
	float YawAngle = 0.0f;
public:
	// Setter
	UFUNCTION(BlueprintCallable)
	void SetRyomaRunState();
	UFUNCTION(BlueprintCallable)
	void SetIsTargeting(bool OutIsTargeting);
	UFUNCTION(BlueprintCallable)
	void SetIsSway(bool OutIsSway);
	
	UFUNCTION(BlueprintCallable)
	void Stopping();
	
	// 이준수 
	FORCEINLINE URyomaCombatComponent* GetRyomaCombatComponent() const { return RyomaCombatComponent; }

	// 이준수, 게임 상황, 전투 상황이 바뀌면 델리게이트에 바인딩되어 호출됨
	UFUNCTION(BlueprintCallable, Category = "GameState")
	void CurrentDefaultsGameState();
	UFUNCTION(BlueprintCallable, Category = "GameState")
	void CurrentCombatGameState(ECombatGameState OutCombatGameState);

	UFUNCTION(BlueprintCallable)
	void SetSwayDirection();
	
	// 이준수, 적을 향해 회전 
	UFUNCTION(BlueprintCallable)
	void MotionWarpingAndRotation();
	
	TArray<AEnemyCharacter*> GetDetectionEnemys();
	void GetEnemiesByDirection(TArray<AEnemyCharacter*> Enemies, TArray<AEnemyCharacter*> &ForwardEnemies, TArray<AEnemyCharacter*> &BackwardEnemies, TArray<AEnemyCharacter*> &RightEnemies, TArray<AEnemyCharacter*> &LeftEnemies);
	void RotateTowardsEnemy(const FVector& MovementVector, const FVector& AttackDirection, AEnemyCharacter* &ForwardEnemy, AEnemyCharacter* &BackwardEnemy, AEnemyCharacter* &RightEnemy, AEnemyCharacter* &LeftEnemy);
	
    AEnemyCharacter* FindNearestEnemy(const FVector& Origin, const TArray<AEnemyCharacter*>& ActorsToCheck, float& Distance);

	void RemoveMotionWarpingTargetAttack();
	
	// 이준수, 전투가 끝났는지를 알기 위한 함수
	UFUNCTION(BlueprintCallable)
	void AllEnemyDection();

	UFUNCTION(BlueprintCallable)
	void SetLightAttackComboCount(int32 OutLightAttackComboCount) { LightAttackComboCount = OutLightAttackComboCount; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetLightAttackComboCount() { return LightAttackComboCount; }
private:
	UPROPERTY()
	TArray<AEnemyCharacter*> DetectionCombatEnemies;
	UPROPERTY()
	int32 DetectedCombatEnemyCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 LightAttackComboCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AEnemyCharacter* TargetCharacter = nullptr;
private:
	FTimerHandle MotionWarpingTimerHandle;
//============================================================================
// 정찬희  , 상호작용 관련 변수와 함수
//============================================================================
public:
	UPROPERTY(VisibleAnywhere , category = "Character | Interaction")
	TScriptInterface<IInteractionInterface> TargetInteractable;

	UPROPERTY(EditAnywhere , category = "Widget")
	TSubclassOf<class UWindowBase> BP_WindowBase;
	UPROPERTY()
	class UWindowBase* WindowBase;

	void SetWindowBase(class UWindowBase* WindowWidget) { WindowBase = WindowWidget; };
	
	UFUNCTION(BlueprintCallable)
	UWindowBase* GetWindowBase() { return WindowBase; }
	
	UPROPERTY(visibleAnywhere , category = "Character | Inventory")
	UInventoryComponent* PlayerInventory;

	void UpdateInteractionWidget() const;
	//상호 작용 확인 빈도
	float InteractionCheckFrequency;
	// 상호작용 가능 거리
	float InteractionCheckDistance;
	//플레이어가 일정 시간 바라보았을 때 상호작용이 가능하게하는 타이머
	FTimerHandle TimerHandle_Interaction;

	//상호 작용 데이터 , 현재 상호 작용이 가능하고 마지막으로 상호작용한 시간을 체크
	FInteractionData InteractionData;

	void PerfomInteractionCheck();
	// 라인 트레이스로 상호작용 가능한 액터가 있는지 체크
	void FoundInteractable(AActor* NewInteractable);
	// 상호작용할 액터가 없을 경우
	void NoInteractableFound();

	// 상호작용 시작과 끝
	void BeginInteract();
	void EndInteract();
	void Interact();

	void ToggleMainMenu();
	
	FOnToggleMainMenu OnToggleMainMenu;
	
	//정찬희 , 상호작용을 하면 Timer를 리턴해주는  Get 함수
	FORCEINLINE bool IsInteracting() const {return GetWorld()->GetTimerManager().IsTimerActive(TimerHandle_Interaction);}
	FORCEINLINE UInventoryComponent* GetInventory() const {return PlayerInventory;}

	UPROPERTY()
	AShopNPC* SellNpc;
private:
	bool bIsInteract = false;
	
	void WindowEsc();
	void WindowSelect();
};
	

