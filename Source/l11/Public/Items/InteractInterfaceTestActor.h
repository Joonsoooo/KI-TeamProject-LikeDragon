// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Items/ItemInterface/InteractionInterface.h"
#include "InteractInterfaceTestActor.generated.h"

class UCapsuleComponent;
UCLASS()
class L11_API AInteractInterfaceTestActor : public AActor , public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractInterfaceTestActor();

	
protected:
	UPROPERTY(EditAnywhere ,Category="Test Actor")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditInstanceOnly ,Category="Test Actor")
	FInteractableData InstanceInteractableData;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	virtual void BeginInteract() override;
	virtual void EndInteract() override;
	virtual void Interact(ARyomaCharacter* PlayerCharacter) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCapsuleComponent* CapsuleComponent;
	

	
};
