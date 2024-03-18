// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToWithCustomRadius.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_MoveToWithCustomRadius::UBTTask_MoveToWithCustomRadius()
{
	NodeName = TEXT("Move To With Custom Radius");


}

EBTNodeResult::Type UBTTask_MoveToWithCustomRadius::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	if (Blackboard == nullptr) {
		//UE_LOG(LogTemp, Warning, TEXT("Move To Failed"));
		return EBTNodeResult::Failed;
	}

	AcceptableRadius = Blackboard->GetValueAsFloat(TEXT("WeaponRange"))-100;

	EBTNodeResult::Type NodeResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	if (NodeResult == EBTNodeResult::Failed) {
		FString ActorName = OwnerComp.GetOwner()->GetName();
		
		Blackboard->SetValueAsBool(TEXT("IsMoveToPlayerPossible"), false);
	}

	return NodeResult;
}