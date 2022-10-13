// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BaseEnemyCharacter.h"
#include "AI/PatrolPath.h"

void ABaseEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));

	EnemyCharacter = Cast<ABaseEnemyCharacter>(GetPawn());
	if (EnemyCharacter != nullptr)
	{
		if (AIBehaviorTree != nullptr)
		{

			UE_LOG(LogTemp, Warning, TEXT("RunBehaviorTree"));
			RunBehaviorTree(AIBehaviorTree);

			GetBlackboardComponent()->SetValueAsBool(TEXT("IsPatrolling"), EnemyCharacter->IsPatrolling);
			if (EnemyCharacter->IsPatrolling)
			{
				GetBlackboardComponent()->SetValueAsBool(TEXT("PatrolPointIndex"), 0);
				GetBlackboardComponent()->SetValueAsObject(TEXT("Path"), EnemyCharacter->PatrolPath);
				GetBlackboardComponent()->SetValueAsFloat(TEXT("DefaultWaitTime"), EnemyCharacter->DefaultWaitTime);
				GetBlackboardComponent()->SetValueAsFloat(TEXT("RandomDeviation"), EnemyCharacter->RandomDeviation);

			}
		}
	}
}

void ABaseEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

