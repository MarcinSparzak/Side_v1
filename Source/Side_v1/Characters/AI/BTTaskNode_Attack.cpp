// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Attack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../BaseEnemyCharacter.h"

EBTNodeResult::Type UBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* AIBlackboard = OwnerComp.GetBlackboardComponent();

	ABaseEnemyCharacter* OwnerActor = Cast<ABaseEnemyCharacter>(AIBlackboard->GetValueAsObject(TEXT("SelfActor")));

	if (OwnerActor == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Owner not found"));
		return EBTNodeResult::Failed;
	}
	FVector PlayerLocation = AIBlackboard->GetValueAsVector(TEXT("PlayerLocation"));

	if (!PlayerLocation.IsZero()) {
		OwnerActor->Attack(PlayerLocation);
	}

	return EBTNodeResult::Type();
}
