// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_SmallRampAttack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../SmallRampCharacter.h"

EBTNodeResult::Type UBTTaskNode_SmallRampAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* AIBlackboard = OwnerComp.GetBlackboardComponent();

	ASmallRampCharacter* OwnerActor = Cast<ASmallRampCharacter>(AIBlackboard->GetValueAsObject(TEXT("SelfActor")));

	if (OwnerActor == nullptr) {
		//UE_LOG(LogTemp, Warning, TEXT("Owner not found"));
		return EBTNodeResult::Failed;
	}
	else {
		FVector PlayerLocation = AIBlackboard->GetValueAsVector(TEXT("PlayerLocation"));

		if (!PlayerLocation.IsZero()) {
			OwnerActor->Attack(PlayerLocation);
		}

		return EBTNodeResult::Succeeded;
	}
}
