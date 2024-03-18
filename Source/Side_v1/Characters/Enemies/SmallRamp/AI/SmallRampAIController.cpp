// Fill out your copyright notice in the Description page of Project Settings.


#include "SmallRampAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../SmallRampCharacter.h"
#include "../../AI/PatrolPath.h"
#include "../../../PlayerCharacter.h"
#include "../../../../Props/Weapons/MeleeBase.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionTypes.h"

void ASmallRampAIController::BeginPlay()
{
	Super::BeginPlay();


	//UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));

	EnemyCharacter = Cast<ASmallRampCharacter>(GetPawn());
	if (EnemyCharacter == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("No Character Found"));
		return;
	}

	if (AIBehaviorTree != nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("RunBehaviorTree"));
		RunBehaviorTree(AIBehaviorTree);
	}

	SetupBlackboard();
	UpdateSightRadius();

	UAIPerceptionComponent* AIPerc = GetAIPerceptionComponent();
	if (AIPerc != nullptr) {
		//UE_LOG(LogTemp, Warning, TEXT("Update Delegate"));
		AIPerc->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ASmallRampAIController::OnTargetPerceptionUpdatedDelegate);

	}

}


ASmallRampAIController::ASmallRampAIController()
{

	SetupAIPerception();
}

void ASmallRampAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ASmallRampAIController::SetupBlackboard()
{

	UBlackboardComponent* AIBlackboard = GetBlackboardComponent();

	if (AIBlackboard == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Blackboard not found"));
		return;
	}

	//UE_LOG(LogTemp, Warning, TEXT("SetupBlackboard"));
	// Character has two weapons of the same BP, we only need one to set up data
	AMeleeBase* Weapon = EnemyCharacter->GetRightHandWeapon();
	if (Weapon != nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Set Weapon Range"));
		float WeaponRange = Weapon->GetWeaponRange();

		AIBlackboard->SetValueAsFloat(TEXT("DistanceFromPlayer"), WeaponRange);
		AIBlackboard->SetValueAsFloat(TEXT("WeaponRange"), WeaponRange);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("No Weapon Found"));
		AIBlackboard->SetValueAsFloat(TEXT("DistanceFromPlayer"), 100.0f);
		AIBlackboard->SetValueAsFloat(TEXT("WeaponRange"), 0.0f);
	}

	AIBlackboard->SetValueAsObject(TEXT("Player"), UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	AIBlackboard->SetValueAsBool(TEXT("IsPatrolling"), EnemyCharacter->IsPatrolling);
	if (EnemyCharacter->IsPatrolling)
	{
		AIBlackboard->SetValueAsBool(TEXT("PatrolPointIndex"), 0);
		AIBlackboard->SetValueAsObject(TEXT("Path"), EnemyCharacter->PatrolPath);
		AIBlackboard->SetValueAsFloat(TEXT("DefaultWaitTime"), EnemyCharacter->DefaultWaitTime);
		AIBlackboard->SetValueAsFloat(TEXT("RandomDeviation"), EnemyCharacter->RandomDeviation);
	}

}

void ASmallRampAIController::OnTargetPerceptionUpdatedDelegate(AActor* Actor, FAIStimulus Stimulus)
{
	//UE_LOG(LogTemp, Warning, TEXT("Perception Update"));

	APlayerCharacter* Target = Cast<APlayerCharacter>(Actor);
	if (Target == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("OnTargetPerceptionUpdatedDelegate: 110: Target nullptr"));
		return;
	}

	UBlackboardComponent* AIBlackboard = GetBlackboardComponent();
	if (Stimulus.WasSuccessfullySensed())
	{
		//UE_LOG(LogTemp, Warning, TEXT("Target sensed"));
		AIBlackboard->SetValueAsVector(TEXT("PlayerLocation"), Actor->GetActorLocation());
		AIBlackboard->SetValueAsObject(TEXT("Player"), Target);
		AIBlackboard->SetValueAsBool(TEXT("IsMoveToPlayerPossible"), true);
	}
	else {
		//UE_LOG(LogTemp, Warning, TEXT("Target not sensed"));
		AIBlackboard->ClearValue(TEXT("PlayerLocation"));
		AIBlackboard->ClearValue(TEXT("Player"));
		AIBlackboard->SetValueAsBool(TEXT("IsMoveToPlayerPossible"), false);
	}
}

void ASmallRampAIController::SetupAIPerception()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component"));
	AISenseConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SenseSight"));

	AISenseConfigSight->DetectionByAffiliation.bDetectFriendlies = false;
	AISenseConfigSight->DetectionByAffiliation.bDetectEnemies = true;
	AISenseConfigSight->DetectionByAffiliation.bDetectNeutrals = true;
	AISenseConfigSight->SightRadius = 2500.0f;
	AISenseConfigSight->LoseSightRadius = 3000.0f;
	AISenseConfigSight->AutoSuccessRangeFromLastSeenLocation = 300.0f;

	AIPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	//AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseEnemyAIController::OnTargetPerceptionUpdatedDelegate);
	AIPerceptionComponent->ConfigureSense(*AISenseConfigSight);

	SetGenericTeamId(FGenericTeamId(2));
}

void ASmallRampAIController::UpdateSightRadius()
{
	UAIPerceptionComponent* AIPerception = GetAIPerceptionComponent();
	if (AIPerception != nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("AI perception found"));
		FAISenseID SenseId = UAISense::GetSenseID(UAISense_Sight::StaticClass());
		UAISenseConfig* SenseConfig = AIPerception->GetSenseConfig(SenseId);
		if (SenseConfig != nullptr)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Sight config found"));
			UAISenseConfig_Sight* ConfigSight = Cast<UAISenseConfig_Sight>(SenseConfig);
			ConfigSight->SightRadius = EnemyCharacter->SightRadius;
			ConfigSight->LoseSightRadius = EnemyCharacter->LoseSightRadius;
			//UE_LOG(LogTemp, Warning, TEXT("Sight Radius %f"), ConfigSight->SightRadius);
			AIPerception->RequestStimuliListenerUpdate();
		}
	}
}



void ASmallRampAIController::UpdateCharacterWeaponAI(float WeaponRange)
{
	if (AIBehaviorTree != nullptr)
	{
		UBlackboardComponent* AIBlackboard = GetBlackboardComponent();

		AIBlackboard->SetValueAsFloat(TEXT("DistanceFromPlayer"), WeaponRange - 100.0f);
		AIBlackboard->SetValueAsFloat(TEXT("WeaponRange"), WeaponRange);
	}
	return;
}

