// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemData/ItemDataStructs.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

class ARyomaCharacter;

UENUM()
enum class EInteractionType : uint8
{
	//주울 때 , NPC , 어떤 장치(문) , 토글이 필요한 어떤 것(스위치) , 정보를 담아둘 곳?
	Pickup UMETA(DisplayName = "Pickup"),
	NonePlayerCharacter UMETA(DisplayName = "NonePlayerCharacter"),
	Device UMETA(DisplayName = "Device"),
	Toggle UMETA(DisplayName = "Toggle"),
	Container UMETA(DisplayName = "Container"),

	
};

USTRUCT()
struct FInteractableData
{
	GENERATED_BODY()

	//생성자 초기화
	FInteractableData() :
	InteractionType(EInteractionType::Pickup) , Name(FText::GetEmpty()) , Action(FText::GetEmpty()) , Quality(EItemQuality::OneStar) ,ItemStatus(), Image(nullptr) , InteractDuration(0.0f) 
	{}
	
	UPROPERTY(EditInstanceOnly)
	EInteractionType InteractionType;
	
	UPROPERTY(EditInstanceOnly)
	FText Name;

	UPROPERTY(EditInstanceOnly)
	FText Action;

	// 픽업 시에만 사용
	UPROPERTY(EditInstanceOnly)
	EItemQuality Quality;

	UPROPERTY(EditInstanceOnly)
	FItemStatus ItemStatus;

	UPROPERTY(EditInstanceOnly)
	UTexture2D* Image;

	//게임에서 벨브를 돌리거나 , 스위치를 누르고 있어야 할 떄 사용 (일정 시간동안 계속 누르고 있어야 하는경우)
	UPROPERTY(EditInstanceOnly)
	float InteractDuration;
	
};
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class L11_API IInteractionInterface
{
	GENERATED_BODY()
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	//일정 거리 이상 가까워지면 상호작용 진행

	virtual void BeginFocus();
	virtual void EndFocus();
	virtual void BeginInteract();
	virtual void EndInteract();
	virtual void Interact(ARyomaCharacter* PlayerCharacter);
	
	//상호작용한 아이템의 정보를 담음
	FInteractableData InteractableData;
};
