// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/InteractInterfaceTestActor.h"
#include "Components/CapsuleComponent.h"
#include "Widget/Interaction/InteractionWidget.h"

// Sets default values
AInteractInterfaceTestActor::AInteractInterfaceTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(Mesh);
	//Mesh->SetupAttachment(RootComponent);

	
	
	//초기 상호작용 액터의 셋팅값
	// InteractableData.Name = FText::FromString("Default Interactable");
	// InteractableData.Action = FText::FromString("See");
	// InteractableData.Quality = EItemQuality::OneStar;
	// InteractableData.InteractDuration = 1.0f;


}

// Called when the game starts or when spawned
void AInteractInterfaceTestActor::BeginPlay()
{
	Super::BeginPlay();

	// InteractableData = InstanceInteractableData;
}

// Called every frame
void AInteractInterfaceTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AInteractInterfaceTestActor::BeginFocus()
{
	if (Mesh)
	{
		Mesh->SetRenderCustomDepth(true);
	}
}

void AInteractInterfaceTestActor::EndFocus()
{
	if (Mesh)
	{
		Mesh->SetRenderCustomDepth(false);
	}
}


void AInteractInterfaceTestActor::BeginInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("BeginInteract Test Actor"));
}

void AInteractInterfaceTestActor::EndInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("EndInteract Test Actor"));
}

void AInteractInterfaceTestActor::Interact(ARyomaCharacter* PlayerCharacter)
{
	
	UE_LOG(LogTemp, Warning, TEXT("Interact Test Actor"));
	
	//델리게이트 실행 , 플레이어 컨트롤러 
}

