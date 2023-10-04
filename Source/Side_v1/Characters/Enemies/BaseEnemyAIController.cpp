// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BaseEnemyCharacter.h"
#include "AI/PatrolPath.h"
#include "../PlayerCharacter.h"
#include "../../Props/Weapons/WeaponBase.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionTypes.h"

void ABaseEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));

	EnemyCharacter = Cast<ABaseEnemyCharacter>(GetPawn());
	if (EnemyCharacter == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Character Found"));
		return;
	}

	if (AIBehaviorTree != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("RunBehaviorTree"));
		RunBehaviorTree(AIBehaviorTree);
	}

	SetupBlackboard();
	UpdateSightRadius();

	UAIPerceptionComponent* AIPerc = GetAIPerceptionComponent();
	if (AIPerc != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Update Delegate"));
		AIPerc->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ABaseEnemyAIController::OnTargetPerceptionUpdatedDelegate);

	}

}


ABaseEnemyAIController::ABaseEnemyAIController()
{

	SetupAIPerception();
}

void ABaseEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ABaseEnemyAIController::SetupBlackboard()
{
	
		UBlackboardComponent* AIBlackboard = GetBlackboardComponent();

		if (AIBlackboard == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Blackboard not found"));
			return;
		}

		//AWeaponBase* Weapon = EnemyCharacter->GetWeapon();
		//if (Weapon != nullptr)
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("Set Weapon Range"));
		//	float WeaponRange = Weapon->GetWeaponRange();

		//	AIBlackboard->SetValueAsFloat(TEXT("DistanceFromPlayer"), WeaponRange - 100.0f);
		//	AIBlackboard->SetValueAsFloat(TEXT("WeaponRange"), WeaponRange);
		//}
		//else
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("No Weapon Found"));
		//	AIBlackboard->SetValueAsFloat(TEXT("DistanceFromPlayer"), 100.0f);
		//	AIBlackboard->SetValueAsFloat(TEXT("WeaponRange"), 0.0f);
		//}

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

void ABaseEnemyAIController::OnTargetPerceptionUpdatedDelegate(AActor* Actor, FAIStimulus Stimulus)
{
	UE_LOG(LogTemp, Warning, TEXT("Perception Update"));
	
	APlayerCharacter* Target = Cast<APlayerCharacter>(Actor);
	if (Target == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Target nullptr"));
		return;
	}

	UBlackboardComponent* AIBlackboard = GetBlackboardComponent();
	if (Stimulus.WasSuccessfullySensed())
	{
		UE_LOG(LogTemp, Warning, TEXT("Target in sight"));
		AIBlackboard->SetValueAsVector(TEXT("PlayerLocation"), Actor->GetActorLocation());
		AIBlackboard->SetValueAsObject(TEXT("Player"), Target);
		AIBlackboard->SetValueAsBool(TEXT("IsMoveToPlayerPossible"), true);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Target out of sight"));
		AIBlackboard->ClearValue(TEXT("PlayerLocation"));
		AIBlackboard->ClearValue(TEXT("Player"));
		AIBlackboard->SetValueAsBool(TEXT("IsMoveToPlayerPossible"), false);
	}
}

void ABaseEnemyAIController::SetupAIPerception()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component"));
	AISenseConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SenseSight"));

	AISenseConfigSight->DetectionByAffiliation.bDetectFriendlies = false;
	AISenseConfigSight->DetectionByAffiliation.bDetectEnemies = true;
	AISenseConfigSight->DetectionByAffiliation.bDetectNeutrals = true;
	AISenseConfigSight->SightRadius = 2500.0f;
	AISenseConfigSight->LoseSightRadius = 3000.0f;

	AIPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	//AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseEnemyAIController::OnTargetPerceptionUpdatedDelegate);
	AIPerceptionComponent->ConfigureSense(*AISenseConfigSight);

	SetGenericTeamId(FGenericTeamId(2));
}

void ABaseEnemyAIController::UpdateSightRadius()
{
	UAIPerceptionComponent* AIPerception = GetAIPerceptionComponent();
	if (AIPerception != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI perception found"));
		FAISenseID SenseId = UAISense::GetSenseID(UAISense_Sight::StaticClass());
		UAISenseConfig* SenseConfig = AIPerception->GetSenseConfig(SenseId);
		if (SenseConfig != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Sight config found"));
			UAISenseConfig_Sight* ConfigSight = Cast<UAISenseConfig_Sight>(SenseConfig);
			ConfigSight->SightRadius = EnemyCharacter->SightRadius;
			ConfigSight->LoseSightRadius = EnemyCharacter->LoseSightRadius;
			UE_LOG(LogTemp, Warning, TEXT("Sight Radius %f"), ConfigSight->SightRadius);
			AIPerception->RequestStimuliListenerUpdate();
		}
	}
}



void ABaseEnemyAIController::UpdateCharacterWeaponAI(float WeaponRange)
{
	if (AIBehaviorTree != nullptr)
	{
		UBlackboardComponent* AIBlackboard = GetBlackboardComponent();

		UE_LOG(LogTemp, Warning, TEXT("Set Weapon Range"));

		AIBlackboard->SetValueAsFloat(TEXT("DistanceFromPlayer"), WeaponRange - 100.0f);
		AIBlackboard->SetValueAsFloat(TEXT("WeaponRange"), WeaponRange);
	}
	return;
}

