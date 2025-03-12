// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BaseAIController.h"

#include "BoneControllers/AnimNode_AnimDynamics.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Utilities/BaseDebugHelper.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

ABaseAIController::ABaseAIController(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	//김동휘, SetDefaultSubobjectClass로 CrowdFollowingComponent 사용
	if (UCrowdFollowingComponent* CrowdFollowingComponent = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		Debug::Print(TEXT("CrowdFollowingComponent valid"), FColor::Green);
	}

	//김동휘, 생성자
	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISenseConfig_Sight"));

	//김동휘, 적 감지
	AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	//김동휘, 아군 감지
	AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	//김동휘, 중립 감지
	AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;
	//김동휘, 시야 반경설정
	AISenseConfig_Sight->SightRadius = 5000.0f;
	//김동휘, 대상을 잃는 시야 범위 설정
	AISenseConfig_Sight->LoseSightRadius = 0.f;
	//김동휘, 주변 시야각
	AISenseConfig_Sight->PeripheralVisionAngleDegrees = 360.f;

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerceptionComponent");
	//김동휘, 센서 설정
	AIPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);
	AIPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ABaseAIController::OnEnemyPerceptionUpdated);

	//김동휘, 생성자 //팀아이디 부여
	SetGenericTeamId(FGenericTeamId(1));
}

ETeamAttitude::Type ABaseAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const APawn* PawnCheck = Cast<const APawn>(&Other);
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<IGenericTeamAgentInterface>(PawnCheck->GetController());

	//김동휘, EQS Test Pawn을 제외시키고 RyomaCharacter만 체크하기 위한 조건 (RyomaCharacter GenericTeamId는 0)
	if (OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() < GetGenericTeamId())
	{
		//김동휘, TeamID가 다르면 적
		return ETeamAttitude::Hostile;
	}

	return ETeamAttitude::Friendly;
}

void ABaseAIController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	//김동휘, update
	if (Stimulus.WasSuccessfullySensed() && Actor)
	{
		if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
		{
			BlackboardComponent->SetValueAsObject(FName(TEXT("TargetActor")), Actor);
		}
	}

	if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
	{
		if (!BlackboardComponent->GetValueAsObject(FName("TargetActor")))
		{
			if (Stimulus.WasSuccessfullySensed() && Actor)
			{
				BlackboardComponent->SetValueAsObject(FName(TEXT("TargetActor")), Actor);
			}
		}
	}
}

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();

	if (UCrowdFollowingComponent* CrowdFollowingComponent = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		CrowdFollowingComponent->SetCrowdSimulationState(bDetourCrowdAvoidence ? ECrowdSimulationState::Enabled : ECrowdSimulationState::Disabled);

		switch (DetourCrowdAvoidenceQuality)
		{
			case 1: CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low); break;
			case 2: CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium); break;
			case 3: CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good); break;
			case 4: CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High); break;
			default: break;
		}

		CrowdFollowingComponent->SetAvoidanceGroup(1);
		CrowdFollowingComponent->SetGroupsToAvoid(1);
		CrowdFollowingComponent->SetCrowdCollisionQueryRange(CollisionQueryRange);
	}
}

