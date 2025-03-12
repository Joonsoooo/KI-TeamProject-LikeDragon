// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Players/RyomaCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MaterialHLSLTree.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "Components/Input/BaseInputComponent.h"
#include "AbilitySystem/BaseGamePlayTags.h"
#include "Controllers/Players/RyomaController.h"
#include "Kismet/KismetMathLibrary.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "Components/Combat/RyomaCombatComponent.h"
#include "DataAssets/StartupData/DataAsset_StartupBase.h"
#include "Components/Combat/RyomaCombatComponent.h"
#include "GameStates/DefaultGameState.h"
#include "EnhancedInputComponent.h"
#include "EnhancedPlayerInput.h"
#include "InputActionValue.h"
#include "Components/SphereComponent.h"
#include "MotionWarpingComponent.h"
#include "Widget/WindowBase.h"
#include "Components/Inventory/InventoryComponent.h"

// 라인트레이스 선 디버그
#include "DrawDebugHelpers.h"
#include "AbilitySystem/Abilities/Players/RyomaGameplayAbility.h"
#include "Characters/Enemies/EnemyCharacter.h"
#include "Items/InteractInterfaceTestActor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/UI/RyomaUIComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/Inventory/ShopNPC.h"

ARyomaCharacter::ARyomaCharacter()
{

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//스프링 암 세팅
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(GetRootComponent());
	CameraArm->TargetArmLength = 400.0f;
	CameraArm->SocketOffset = FVector(0.f, 0.f, 60.0f);
	CameraArm->bUsePawnControlRotation = true;

	//카메라 세팅
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	//캐릭터 무브먼트 세팅
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.0f;

	//메시 세팅
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/Asset/Character/Main/Ryoma/ryoma_sin.ryoma_sin"));

	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}
	
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -100.f), FRotator(0.f, -90.f, 0.f));

	RyomaCombatComponent = CreateDefaultSubobject<URyomaCombatComponent>(TEXT("RyomaCombat"));

	// 이준수, 료마 상태값 생성
	RyomaState = CreateDefaultSubobject<ARyomaState>(TEXT("RyomaState"));
	
	// 정찬희 , 상호작용하려면 보고 있어야하는 시간 , 상호작용 가능한 거리

	PlayerInventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("PlayerInventory"));
	PlayerInventory->SetSlotCapacity(24);
	
	InteractionCheckFrequency = 1.0f;
	InteractionCheckDistance = 400.0f;
	
	RyomaUIComponent = CreateDefaultSubobject<URyomaUIComponent>(TEXT("RyomaUIComponent"));

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShopNPC::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		if (Actor)
		{
			SellNpc = Cast<AShopNPC>(Actor);
		}
	}


	
}

void ARyomaCharacter::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Begin"));

	
	// 이준수, 플레이어 스테이트, 컨트롤러 접근
	RyomaController = Cast<ARyomaController>(Controller);
	RyomaState = Cast<ARyomaState>(RyomaController->PlayerState);

	// 이준수, 게임 스테이트 접근 + 게임 스테이트의 델리게이트와 바인딩 
	if (ADefaultGameState* DefaultsGameState = Cast<ADefaultGameState>(GetWorld()->GetGameState()))
	{
		//DefaultsGameState->SetCombatGameStateChanged.AddDynamic(this, &ARyomaCharacter::CurrentDefaultsGameState);

		//UE_LOG(LogTemp, Warning, TEXT("CastDefaultGameState"));
		DefaultsGameState->SetCombatGameStateChanged.AddDynamic(this, &ARyomaCharacter::CurrentCombatGameState);

		if (DefaultsGameState->GetCombatGameState() == ECombatGameState::BattleStart)
		{
			CurrentCombatGameState(ECombatGameState::BattleStart);
		}
	}
	
	//정찬희
	if (BP_WindowBase)
	{
		WindowBase = Cast<UWindowBase>(CreateWidget<UWindowBase>( GetWorld(), BP_WindowBase));
		if (WindowBase)
		{
			WindowBase->AddToViewport();
			WindowBase->SetVisibility(ESlateVisibility::Visible);
		}
		
	}

	SetWindowBase(WindowBase);

}



void ARyomaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset as input config"));

	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem);
	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	UBaseInputComponent* BaseInputComponent = CastChecked<UBaseInputComponent>(PlayerInputComponent);
	BaseInputComponent->BindNativeInputAction(InputConfigDataAsset, BaseGameplayTags::Chara_Ability_DefaultMode_Look, ETriggerEvent::Triggered, this, &ARyomaCharacter::Input_Look);
	BaseInputComponent->BindNativeInputAction(InputConfigDataAsset, BaseGameplayTags::Chara_Ability_DefaultMode_Move, ETriggerEvent::Triggered, this, &ARyomaCharacter::Input_Move);
	BaseInputComponent->BindNativeInputAction(InputConfigDataAsset, BaseGameplayTags::Chara_Ability_DefaultMode_Run, ETriggerEvent::Started, this, &ARyomaCharacter::Input_Run);
	BaseInputComponent->BindNativeInputAction(InputConfigDataAsset, BaseGameplayTags::Chara_Ability_DefaultMode_Walk, ETriggerEvent::Triggered, this, &ARyomaCharacter::Input_PressedWalk);
	BaseInputComponent->BindNativeInputAction(InputConfigDataAsset, BaseGameplayTags::Chara_Ability_DefaultMode_Walk, ETriggerEvent::Completed, this, &ARyomaCharacter::Input_ReleasedWalk);
	
	//정찬희 , 상호작용 인풋 , 
	BaseInputComponent->BindNativeInputAction(InputConfigDataAsset, BaseGameplayTags::Chara_Ability_DefaultMode_Input_Interact, ETriggerEvent::Started, this, &ARyomaCharacter::BeginInteract);
	BaseInputComponent->BindNativeInputAction(InputConfigDataAsset, BaseGameplayTags::Chara_Ability_DefaultMode_Input_Interact, ETriggerEvent::Completed, this, &ARyomaCharacter::EndInteract);
	BaseInputComponent->BindNativeInputAction(InputConfigDataAsset, BaseGameplayTags::Chara_Ability_DefaultMode_Input_OpenMenu, ETriggerEvent::Completed, this, &ARyomaCharacter::ToggleMainMenu);
	BaseInputComponent->BindNativeInputAction(InputConfigDataAsset, BaseGameplayTags::Chara_Ability_DefaultMode_Input_Selcet, ETriggerEvent::Completed, this, &ARyomaCharacter::WindowSelect);
	BaseInputComponent->BindNativeInputAction(InputConfigDataAsset, BaseGameplayTags::Chara_Ability_DefaultMode_Input_ESC, ETriggerEvent::Completed, this, &ARyomaCharacter::WindowEsc);
	
	//이준수 , 몰라
	BaseInputComponent->BindAbilityInputPressedAction(InputConfigDataAsset, this, &ARyomaCharacter::Input_AbilityInputPressed);
	BaseInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ARyomaCharacter::Input_AbilityInputPressed, &ARyomaCharacter::Input_AbilityInputReleased);
}

UPawnCombatComponent* ARyomaCharacter::GetPawnCombatComponent() const 
{
	return RyomaCombatComponent;
}

void ARyomaCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (BaseAbilitySystemComponent && BaseAttributeSet)
	{
		//UE_LOG(LogTemp, Log, TEXT("AbilitySystemComponent initialized in PossessedBy for %s"), *GetNameSafe(CurrentActorInfo()->BaseAbilitySystemComponent);
	}

	if (!StartupData.IsNull())
	{
		if (UDataAsset_StartupBase* LoadData = StartupData.LoadSynchronous())
		{
			//Startup데이터가 Null이 아닌경우 StartupData는 동기화로드를 거쳐서 최종적으로 게임어빌리티시스템이 발동된다. 
			LoadData->GiveToAbilitySystemComponent(GetBaseAbilitySystemComponent());
		}
	}
}

UPawnUIComponent* ARyomaCharacter::GetPawnUIComponent() const
{
	return RyomaUIComponent;
}

URyomaUIComponent* ARyomaCharacter::GetRyomaUIComponent() const
{
	return RyomaUIComponent;
}

void ARyomaCharacter::Input_Move(const FInputActionValue& InputActionValue)
{

	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

	if (MovementVector.Y != 0.0f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}
	if (MovementVector.X != 0.0f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}


void ARyomaCharacter::Input_Look(const FInputActionValue& InputActionValue)
{

	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}

	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ARyomaCharacter::Input_Run()
{

	if (FMath::IsNearlyEqual(GetCharacterMovement()->Velocity.Size(), 400.0f, 0.1f))
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;

		if (RyomaState)
		{
			// Shift를 누르면 Run 상태로 변환
			RyomaState->SetRunState(ERunState::Run);
			RunState.ExecuteIfBound(ERunState::Run);

			// 5초 후 Run 상태에서 Tired 상태로 변환 
			GetWorld()->GetTimerManager().SetTimer(
				RunTimerHandle,
				this,
				&ARyomaCharacter::SetRyomaRunState,
				5.0f,
				false
			);
		}
	}
	else if (FMath::IsNearlyEqual(GetCharacterMovement()->Velocity.Size(), 600.0f, 0.1f))
	{
		GetCharacterMovement()->MaxWalkSpeed = 400.0f;

		RyomaState->SetRunState(ERunState::None);
		RunState.ExecuteIfBound(ERunState::None);
		GetWorld()->GetTimerManager().ClearTimer(RunTimerHandle);
	}

}

void ARyomaCharacter::Input_PressedWalk()
{

	if (FMath::IsNearlyEqual(GetCharacterMovement()->Velocity.Size(), 400.0f, 0.1f))
	{
		GetCharacterMovement()->MaxWalkSpeed = 200.0f;
	}
}

void ARyomaCharacter::Input_ReleasedWalk()
{
	if (FMath::IsNearlyEqual(GetCharacterMovement()->Velocity.Size(), 200.0f, 0.1f))
	{
		GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	}
}


void ARyomaCharacter::Input_AbilityInputPressed(FGameplayTag InputTag)
{
	BaseAbilitySystemComponent->OnAbilityInputPressed(InputTag);
}

void ARyomaCharacter::Input_AbilityInputReleased(FGameplayTag InputTag)
{
	BaseAbilitySystemComponent->OnAbilityInputReleased(InputTag);
}



void ARyomaCharacter::SetRyomaRunState()
{
	if (RyomaState)
	{
		if (RyomaState->GetRunState() == ERunState::Run)
		{
			// Run에서 Tired 상태로 변환 
			RyomaState->SetRunState(ERunState::Tired);
			RunState.ExecuteIfBound(ERunState::Tired);

			// Tired 상태에서 3초 후에 Stop로 상태 변환 
			GetWorld()->GetTimerManager().SetTimer(
				RunTimerHandle,
				this,
				&ARyomaCharacter::SetRyomaRunState,
				3.0f,
				false
			);
		}
		else if (RyomaState->GetRunState() == ERunState::Tired)
		{
			RyomaState->SetRunState(ERunState::Stop);
			RunState.ExecuteIfBound(ERunState::Stop);

			/*GetWorld()->GetTimerManager().SetTimer(
				RunTimerHandle,
				this,
				&ARyomaCharacter::SetRyomaRunState,
				3.0f,
				false*/

			GetWorld()->GetTimerManager().SetTimer(
				RunTimerHandle,
				this,
				&ARyomaCharacter::Stopping,
				0.1f,
				true
			);
		}
		else if (RyomaState->GetRunState() == ERunState::Stop)
		{
			/*RyomaState->SetRunState(ERunState::None);
			RunState.ExecuteIfBound(ERunState::None);*/

			/*GetWorld()->GetTimerManager().SetTimer(
				RunTimerHandle,
				this,
				&ARyomaCharacter::Stopping,
				0.1f,
				true
			);*/
		}
	}
}

void ARyomaCharacter::SetIsTargeting(bool OutIsTargeting)
{
	IsTargeting = OutIsTargeting;
	Targeting.ExecuteIfBound(IsTargeting);
}

void ARyomaCharacter::SetIsSway(bool OutIsSway)
{
	IsSway = OutIsSway;
	Sway.ExecuteIfBound(IsSway);
}


void ARyomaCharacter::Stopping()
{
	UE_LOG(LogTemp, Warning, TEXT("Stopping"));


	StartTime += 0.1f; // 시간 증가
	float ProgressRate = StartTime / EndTime;
	ProgressRate = FMath::Clamp(ProgressRate, 0.0f, 1.0f); // 0 ~ 1 사이로 제한

	// 천천히 줄어들다가 갈 수록 빠르게 줄어듦
	float SmoothRate = FMath::Pow(ProgressRate, 3.0f); // t^3 감속 방식

	float CurrentWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	GetCharacterMovement()->MaxWalkSpeed = CurrentWalkSpeed * (1.0f - SmoothRate);
	UE_LOG(LogTemp, Warning, TEXT("Current Time : %f, Current WalkSpeed : %f"), StartTime, GetCharacterMovement()->MaxWalkSpeed);

	if  (FMath::IsNearlyEqual(StartTime, 3.0f, 0.001f))
	{
		GetWorld()->GetTimerManager().ClearTimer(RunTimerHandle);
		StartTime = 0.f;
	}
}

void ARyomaCharacter::CurrentDefaultsGameState()
{
	if (ADefaultGameState* DefaultsGameState = Cast<ADefaultGameState>(GetWorld()->GetGameState()))
	{
		
	}
}

void ARyomaCharacter::CurrentCombatGameState(ECombatGameState OutCombatGameState)
{
	// DefaultsGameState에 접근
	if (ADefaultGameState* DefaultsGameState = Cast<ADefaultGameState>(GetWorld()->GetGameState()))
	{
		// ECombatGameState가 BattleStart라면 GA_Ryoma_EquipKatana_tachi 능력 활성화
		if (DefaultsGameState->GetCombatGameState() == ECombatGameState::BattleStart)
		{	
			
			UE_LOG(LogTemp, Warning, TEXT("BattleStart"));

			// 캐릭터의 AbilitySystemComponent 가져오기
			if (UBaseAbilitySystemComponent* AbilitySystem = FindComponentByClass<UBaseAbilitySystemComponent>())
			{
				// 블루프린트 어빌리티 클래스의 경로 (로드 필요)
				if (TSubclassOf<URyomaGameplayAbility> AbilityClass = LoadClass<URyomaGameplayAbility>(nullptr, TEXT("/Game/Like/BP_/Characters/Ryoma/GA/GA_Ryoma_EquipKatana_tachi.GA_Ryoma_EquipKatana_tachi_C")))
				{
					// 어빌리티 클래스를 사용하여 어빌리티 활성화
					AbilitySystem->TryActivateAbilityByClass(AbilityClass);
				}
			}
		}
	}
	AllEnemyDection();
}

void ARyomaCharacter::SetSwayDirection()
{
	FVector MovementVector = GetLastMovementInputVector();
	FRotator CharacterRotation = GetActorRotation(); // 캐릭터의 현재 회전 값

	// 메시의 기본 Yaw 오프셋을 보정 (예: 메시 Yaw 기본값이 -90인 경우)
	float MeshYawOffset = -90.0f;
	CharacterRotation.Yaw += MeshYawOffset;
	
	// 2. 로컬 기준 전방 및 오른쪽 벡터 계산
	FVector ForwardDirection = CharacterRotation.RotateVector(FVector::ForwardVector); // 캐릭터 기준 전방
	FVector RightDirection = CharacterRotation.RotateVector(FVector::RightVector);     // 캐릭터 기준 오른쪽
	
	// 3. 입력 벡터를 캐릭터 로컬 좌표계로 변환
	SwayDirection = (ForwardDirection * MovementVector.Y) + (RightDirection * MovementVector.X);
	SwayDirection.Normalize();
	
	// 4. 변환된 벡터를 각도로 변환
	FRotator AttackRotation = SwayDirection.Rotation(); // 방향을 Rotator로 변환
	YawAngle = AttackRotation.Yaw; // -180 ~ 180 범위의 Yaw 값
	
	// 결과 출력 (-180 ~ 180도)
	//UE_LOG(LogTemp, Warning, TEXT("Relative Input Angle: %f"), YawAngle);

	

	if (MovementVector.IsNearlyZero())
	{
		YawAngle = -180.0f;
	}
	
	//UE_LOG(LogTemp, Warning, TEXT("Calculated Angle: %f"), YawAngle);
}

void ARyomaCharacter::MotionWarpingAndRotation()
{
	FVector MovementVector = GetLastMovementInputVector();
	
	//FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f); // 카메라의 회전 값 
	//FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
	//FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
	FVector ForwardDirection = FVector::ForwardVector; // 월드 기준의 전방 (X+ 방향)
	FVector RightDirection = FVector::RightVector; // 월드 기준의 오른쪽 (Y+ 방향)
	FVector AttackDirection = (ForwardDirection * MovementVector.X) + (RightDirection * MovementVector.Y);
	AttackDirection.Normalize();
	
	FRotator CurrentRotation = GetActorRotation();
	FRotator TargetRotation = FRotator(CurrentRotation.Pitch, AttackDirection.Rotation().Yaw, CurrentRotation.Roll);
	
	TArray<AEnemyCharacter*> DetectedEnemies = GetDetectionEnemys();

	// 감지된 적이 없을 때 
	if (DetectedEnemies.Num() == 0)
	{
		// 감지된 적도 없고 키 입력도 없을 때
		if (MovementVector.IsNearlyZero())
		{
			//UE_LOG(LogTemp, Warning, TEXT("0"));
			return;
		}
		// 감지된 적은 없지만 키 입력은 있을 때 
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("1"));

			float YawDifference = FMath::FindDeltaAngleDegrees(GetActorRotation().Yaw, TargetRotation.Yaw);
			float ClampedYaw = FMath::Clamp(YawDifference, -45.0f, 45.0f); // 최대 45도만 회전
			TargetRotation.Yaw = CurrentRotation.Yaw + ClampedYaw; // 제한된 회전 적용
			FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), 100.0f);
			SetActorRotation(NewRotation); // 캐릭터의 회전 적용

			return;
		}
	}
		
	TArray<AEnemyCharacter*> ForwardEnemies, BackwardEnemies, RightEnemies, LeftEnemies;
	
	GetEnemiesByDirection(DetectedEnemies, ForwardEnemies, BackwardEnemies, RightEnemies, LeftEnemies);

	float Distance = 0.0f;
	AEnemyCharacter* ForwardEnemy = nullptr;
	AEnemyCharacter* BackwardEnemy = nullptr;
	AEnemyCharacter* RightEnemy = nullptr;
	AEnemyCharacter* LeftEnemy = nullptr;
	
	if (ForwardEnemies.Num() > 0)
	{
		ForwardEnemy = FindNearestEnemy(GetActorLocation(), ForwardEnemies, Distance);
		//UE_LOG(LogTemp, Warning, TEXT("8"));

	}
	if (BackwardEnemies.Num() > 0)
	{
		BackwardEnemy = FindNearestEnemy(GetActorLocation(), BackwardEnemies, Distance);
		//UE_LOG(LogTemp, Warning, TEXT("9"));
	}
	if (RightEnemies.Num() > 0)
	{
		RightEnemy = FindNearestEnemy(GetActorLocation(), RightEnemies, Distance);
		//UE_LOG(LogTemp, Warning, TEXT("10"));
	}
	if (LeftEnemies.Num() > 0)
	{
		LeftEnemy = FindNearestEnemy(GetActorLocation(), LeftEnemies, Distance);
		//UE_LOG(LogTemp, Warning, TEXT("11"));

	}
	
	RotateTowardsEnemy(MovementVector, AttackDirection, ForwardEnemy, BackwardEnemy, RightEnemy, LeftEnemy);
}

TArray<AEnemyCharacter*> ARyomaCharacter::GetDetectionEnemys()
{
	TArray<FHitResult> HitResults;
	float TraceDistance = 300.0f;
	FVector TraceBoxSize = FVector(300.0f, 600.0f, 100.0f);
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceChannel;
	TEnumAsByte<EObjectTypeQuery> Pawn = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn);
	TraceChannel.Add(Pawn);
	FVector TraceStart = GetActorLocation() - (GetActorForwardVector() * TraceDistance / 2);
	FVector TraceEnd = GetActorLocation() + (GetActorForwardVector() * TraceDistance / 2);

	TArray<AEnemyCharacter*> DetectionEnemys;

	// 적을 찾기 위해 BoxTrace 실행
	UKismetSystemLibrary::BoxTraceMultiForObjects(
		this,
		TraceStart,
		TraceEnd,
		TraceBoxSize / 2,
		GetActorForwardVector().ToOrientationRotator(),
		TraceChannel,
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::None,
		HitResults,
		true
	);

	// 감지된 적들 추가
	for (const FHitResult& HitResult : HitResults)
	{
		if (AActor* HitActor = HitResult.GetActor())
		{
			if (HitActor != this)
			{
				if (AEnemyCharacter* HitEnemy = Cast<AEnemyCharacter>(HitActor))
				{
					DetectionEnemys.AddUnique(HitEnemy);
				}
			}
		}
	}
	
	return DetectionEnemys;
	
}

void ARyomaCharacter::GetEnemiesByDirection(TArray<AEnemyCharacter*> Enemies, TArray<AEnemyCharacter*> &ForwardEnemies, TArray<AEnemyCharacter*> &BackwardEnemies, TArray<AEnemyCharacter*> &RightEnemies, TArray<AEnemyCharacter*> &LeftEnemies)
{
	//UE_LOG(LogTemp, Warning, TEXT("3"));

	for (AEnemyCharacter* HitEnemy : Enemies)
	{
		//  내 위치에서 적의 위치로 향하는 방향 벡터 
		FVector DirectionToEnemy = (HitEnemy->GetActorLocation() - GetActorLocation()).GetSafeNormal();

		//  내 위치의 Forward, Right 벡터와의 내적을 계산 
		float ForwardDot = FVector::DotProduct(GetActorForwardVector(), DirectionToEnemy); // Y축을 기준으로 하는 전방
		float RightDot = FVector::DotProduct(GetActorRightVector(), DirectionToEnemy); // X축을 기준으로 하는 우측
		
		// 전방
		if (ForwardDot > 0.707f && FMath::Abs(RightDot) < 0.707f) 
		{
			//UE_LOG(LogTemp, Warning, TEXT("4"));

			ForwardEnemies.AddUnique(HitEnemy);
		}
		// 후방
		else if (ForwardDot < -0.707f && FMath::Abs(RightDot) < 0.707f) 
		{
			//UE_LOG(LogTemp, Warning, TEXT("5"));

			BackwardEnemies.AddUnique(HitEnemy);
		}
		// 우측
		else if (FMath::Abs(ForwardDot) < 0.707f && RightDot > 0.707f) 
		{
			//UE_LOG(LogTemp, Warning, TEXT("6"));

			RightEnemies.AddUnique(HitEnemy);
		}
		// 좌측
		else if (FMath::Abs(ForwardDot) < 0.707f && RightDot < -0.707f) 
		{
			//UE_LOG(LogTemp, Warning, TEXT("7"));

			LeftEnemies.AddUnique(HitEnemy);
		}
	}
}

void ARyomaCharacter::RotateTowardsEnemy(const FVector& MovementVector, const FVector& AttackDirection,
	AEnemyCharacter* &ForwardEnemy, AEnemyCharacter* &BackwardEnemy, AEnemyCharacter* &RightEnemy, AEnemyCharacter* &LeftEnemy)
{
	//UE_LOG(LogTemp, Warning, TEXT("12"));
	
	TargetCharacter = nullptr;
	TMap<FVector, AEnemyCharacter*> DirectionToEnemyMap; // 방향과 타겟 

	//UE_LOG(LogTemp, Warning, TEXT("%f"),GetDistanceTo(ForwardEnemy));
	
	if (IsValid(ForwardEnemy) && GetDistanceTo(ForwardEnemy) <= 250.0f && GetDistanceTo(ForwardEnemy) >= 200.0f)
	{
		FMotionWarpingTarget MotionWarpingTarget;
		MotionWarpingTarget.Name = FName("AttackTarget");
		MotionWarpingTarget.Location = ForwardEnemy->GetActorLocation();
		MotionWarpingTarget.Rotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ForwardEnemy->GetActorLocation());
		
		MotionWarpingComponent->AddOrUpdateWarpTarget(MotionWarpingTarget);
		
		//FString Message = TEXT("MotionWarp");
		//Debug::Print(Message, FColor::Red);

		GetWorld()->GetTimerManager().SetTimer(MotionWarpingTimerHandle, this, &ARyomaCharacter::RemoveMotionWarpingTargetAttack, 1.0f, false);
		
		return;
	}
	if (IsValid(ForwardEnemy))
	{
		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ForwardEnemy->GetActorLocation());
		FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 50.0f);
		SetActorRotation(NewRotation);

		TargetCharacter = ForwardEnemy;
	}

	if (IsValid(BackwardEnemy))
	{
	    //UE_LOG(LogTemp, Warning, TEXT("13"));

	    FVector DirectionToEnemy = (BackwardEnemy->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	    float DotProduct = FVector::DotProduct(AttackDirection, DirectionToEnemy);

	    if (DotProduct > 0.707f) // Backward 방향에 가까움
	    {
	        FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), BackwardEnemy->GetActorLocation());
	        FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 100.0f);
	        SetActorRotation(NewRotation);

	        //UE_LOG(LogTemp, Warning, TEXT("Rotating towards Backward enemy: %s"), *BackwardEnemy->GetName());

			TargetCharacter = BackwardEnemy;
	    }
	}

	if (IsValid(RightEnemy))
	{
	    //UE_LOG(LogTemp, Warning, TEXT("14"));

	    FVector DirectionToEnemy = (RightEnemy->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	    float DotProduct = FVector::DotProduct(AttackDirection, DirectionToEnemy);

	    if (DotProduct > 0.707f) // Right 방향에 가까움
	    {
	        FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), RightEnemy->GetActorLocation());
	        FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 100.0f);
	        SetActorRotation(NewRotation);

	        //UE_LOG(LogTemp, Warning, TEXT("Rotating towards Right enemy: %s"), *RightEnemy->GetName());

			TargetCharacter = RightEnemy;
	    }
	}

	if (IsValid(LeftEnemy))
	{
	    //UE_LOG(LogTemp, Warning, TEXT("15"));

	    FVector DirectionToEnemy = (LeftEnemy->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	    float DotProduct = FVector::DotProduct(AttackDirection, DirectionToEnemy);

	    if (DotProduct > 0.707f) // Left 방향에 가까움
	    {
	        FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), LeftEnemy->GetActorLocation());
	        FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 100.0f);
	        SetActorRotation(NewRotation);

	        //UE_LOG(LogTemp, Warning, TEXT("Rotating towards Left enemy: %s"), *LeftEnemy->GetName());

			TargetCharacter = LeftEnemy;
	    }
	}
	
}


AEnemyCharacter* ARyomaCharacter::FindNearestEnemy(const FVector& Origin, const TArray<AEnemyCharacter*>& ActorsToCheck, float& Distance)
{
	AEnemyCharacter* NearestActor = nullptr;
	float DistanceFromNearestActor = Distance = TNumericLimits<float>::Max();

	for (AEnemyCharacter* ActorToCheck : ActorsToCheck)
	{
		if (ActorToCheck)
		{
			const float DistanceFromActorToCheck = (Origin - ActorToCheck->GetActorLocation()).SizeSquared();
			if (DistanceFromActorToCheck < DistanceFromNearestActor)
			{
				NearestActor = ActorToCheck;
				DistanceFromNearestActor = DistanceFromActorToCheck;
			}
		}
	}

	if (NearestActor)
	{
		Distance = FMath::Sqrt(DistanceFromNearestActor);
	}

	return NearestActor;
}

void ARyomaCharacter::RemoveMotionWarpingTargetAttack()
{
	MotionWarpingComponent->RemoveWarpTarget(FName("AttackTarget"));
}

void ARyomaCharacter::AllEnemyDection()
{
	DetectedCombatEnemyCount = 0;
	TArray<FHitResult> HitResults;
	float TraceDistance = 1000.0f;
	FVector TraceBoxSize = FVector(1000.0f, 1000.0f, 100.0f);
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceChannel;
	TEnumAsByte<EObjectTypeQuery> Pawn = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn);
	TraceChannel.Add(Pawn);
	FVector TraceStart = GetActorLocation() - (GetActorForwardVector() * TraceDistance);
	FVector TraceEnd = GetActorLocation() + (GetActorForwardVector() * TraceDistance);

	TArray<AEnemyCharacter*> DetectionEnemys;

	// 적을 찾기 위해 BoxTrace 실행
	UKismetSystemLibrary::BoxTraceMultiForObjects(
		this,
		TraceStart,
		TraceEnd,
		TraceBoxSize,
		GetActorForwardVector().ToOrientationRotator(),
		TraceChannel,
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::None,
		HitResults,
		true
	);

	// 감지된 적들 추가
	for (const FHitResult& HitResult : HitResults)
	{
		if (AActor* HitActor = HitResult.GetActor())
		{
			if (HitActor != this)
			{
				if (AEnemyCharacter* HitEnemy = Cast<AEnemyCharacter>(HitActor))
				{
					DetectionCombatEnemies.AddUnique(HitEnemy);
				}
			}
		}
	}

	if (ADefaultGameState* DefaultsGameState = Cast<ADefaultGameState>(GetWorld()->GetGameState()))
	{
		DefaultsGameState->DetectedCombatEnemy = DetectionCombatEnemies.Num();

		//UE_LOG(LogTemp, Warning, TEXT("%d"), DefaultsGameState->DetectedCombatEnemy);
	}
	
}

void ARyomaCharacter::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);
	
	
	// 마지막 상호작용 시간이 상화작용확인 시간보다 크다면 , 상호작용을 하려면 플레이어가 일정시간 쳐다보고 있어야함
	if (GetWorld()->TimeSince(InteractionData.LastInteractionCheckTime) > InteractionCheckFrequency)
	{
		//라인트레이스 실행
		PerfomInteractionCheck();
	}

	
}

void ARyomaCharacter::UpdateInteractionWidget() const
{
	if (IsValid(TargetInteractable.GetObject()))
	{
		WindowBase->UpdateInteractionWidget(&TargetInteractable->InteractableData);
	}
}

//============================================================== 
// 정찬희 , 상호작용 함수 구현
//==============================================================
void ARyomaCharacter::PerfomInteractionCheck()
{
	// 월드 타임을 가져옴
	InteractionData.LastInteractionCheckTime = GetWorld()->GetTimeSeconds();

	FVector TraceStart{GetPawnViewLocation()};
	FVector TraceEnd{TraceStart + (GetViewRotation().Vector())* InteractionCheckDistance };

	float LookDirection = FVector::DotProduct(GetActorForwardVector(), GetViewRotation().Vector());
	
	if (LookDirection > 0.0f)
	{
		// 라인트레이스 디버그 라인
		DrawDebugLine(GetWorld() , TraceStart , TraceEnd , FColor::Red , false , 1.0f , 0 , 2.0f);
		// 라인트레이스 관련 구조체
		FCollisionQueryParams QueryParams;
		//자기 자신은 무시
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;
		//라인트레이스 실행 시 충돌할 때 결과를 담을 구조체
		FHitResult TraceHit;
		if (GetWorld()->LineTraceSingleByChannel(TraceHit , TraceStart , TraceEnd , ECC_Visibility , QueryParams))
		{
			if (AActor* HitActor = TraceHit.GetActor())
			{
				if (HitActor->Implements<UInteractionInterface>())
				{
					AShopNPC* HitCharacter = Cast<AShopNPC>(HitActor);
					if (HitCharacter)
					{
						if (TraceHit.GetActor() != InteractionData.ShopNPC)
						{
							FoundInteractable(HitCharacter);
							return;
						}
						if (TraceHit.GetActor() == InteractionData.ShopNPC)
						{
							return;
						}
					}
					else
					{
						//현재 상호 작용 중이 아니고 상호작용이 가능한 거리보다 작다면 
						if (TraceHit.GetActor() != InteractionData.CurrentInteractable)
						{
							FoundInteractable(TraceHit.GetActor());
							return;
						}
						if (TraceHit.GetActor() == InteractionData.CurrentInteractable)
						{
							return;
						}
					}
				}
				
			}
		}
	}
	//바라보지 않을 때
	NoInteractableFound();
}

//상호작용이 가능한 액터를 찾았을 때
void ARyomaCharacter::FoundInteractable(AActor* NewInteractable)
{
	//캐릭터가 상호 작용 중이라면
	if (IsInteracting())
	{
		EndInteract();
	}
	//상호작용 대상이라면
	if (InteractionData.CurrentInteractable)
	{
		//목표 상호작용 액터에 저장
		TargetInteractable = InteractionData.CurrentInteractable;
		TargetInteractable->EndFocus();
	}

	// 인터페으스 하
	if (NewInteractable)
	{
		AShopNPC* IsShopNPC = Cast<AShopNPC>(NewInteractable);
		if (IsShopNPC)
		{
			InteractionData.ShopNPC = IsShopNPC;
			TargetInteractable = NewInteractable;
			WindowBase->UpdateInteractionWidget(&TargetInteractable->InteractableData);
		}
		else
		{
			InteractionData.CurrentInteractable = NewInteractable;
			TargetInteractable = NewInteractable;
			WindowBase->UpdateInteractionWidget(&TargetInteractable->InteractableData);
		}
		
	}
	

	//TargetInteractable->BeginFocus();
}

void ARyomaCharacter::NoInteractableFound()
{

	//상호작용할 액터을 찾을 수 없지만 타이머가 작동 중이면
	if (IsInteracting())
	{//타이머 초기화
		GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);
	}
	// 현재 상호작용 항목이 유효하다면
	if (InteractionData.CurrentInteractable)
	{	//상호작용이 가능한 액터라면

		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->EndFocus();
		}
		WindowBase->HideInteractionWidget();
		//초기화
		InteractionData.CurrentInteractable = nullptr;
		TargetInteractable = nullptr;
	}
	else if (InteractionData.ShopNPC)
	{
		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->EndFocus();
		}
		WindowBase->HideInteractionWidget();
		//초기화
		InteractionData.ShopNPC = nullptr;
		TargetInteractable = nullptr;
	}
	EndInteract();

	
}


// 바라보고 있을 떄 발생하는 함수
void ARyomaCharacter::BeginInteract()
{
	if (InteractionData.CurrentInteractable || InteractionData.ShopNPC)
	{
		if (IsValid(TargetInteractable.GetObject()))
		{
			UE_LOG(LogTemp, Error, TEXT("CurrentInteractable BeginInteract"));
			TargetInteractable->BeginInteract();
			float InteractDurationData = 0;
			
			InteractDurationData = TargetInteractable->InteractableData.InteractDuration;
			WindowBase->UpdateInteractionWidget(&TargetInteractable->InteractableData);
		
			if (FMath::IsNearlyZero(InteractDurationData , 0.1f))
			{
				UE_LOG(LogTemp, Warning, TEXT("Interacting"));
				Interact();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("NOInteracting"));
				GetWorldTimerManager().SetTimer(TimerHandle_Interaction , this , &ARyomaCharacter::Interact , InteractDurationData , false);
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("BeginInteract"));

}

void ARyomaCharacter::EndInteract()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);
	if (IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->EndInteract();
	}
}


// 키 입력 시 발생하는 함수
void ARyomaCharacter::Interact()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);
	if (IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->Interact(this);	
	}
	
}

void ARyomaCharacter::ToggleMainMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("ToggleMainMenu"));
	WindowBase->ToggleMainMenu();
}

void ARyomaCharacter::WindowEsc()
{
	WindowBase->MainWindowsESC();
}

void ARyomaCharacter::WindowSelect()
{
	WindowBase->MainWindowsSelect();
}