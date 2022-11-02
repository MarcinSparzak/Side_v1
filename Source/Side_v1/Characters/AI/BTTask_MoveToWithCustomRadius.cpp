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
		UE_LOG(LogTemp, Warning, TEXT("Move To Failed"));
		return EBTNodeResult::Failed;
	}

	AcceptableRadius = Blackboard->GetValueAsFloat(TEXT("WeaponRange"));
	//EBTNodeResult::Type NodeResult = EBTNodeResult::InProgress;

	UE_LOG(LogTemp, Warning, TEXT("Execute Moving"));
	EBTNodeResult::Type NodeResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	UE_LOG(LogTemp, Warning, TEXT("Node Result %s"), *UEnum::GetValueAsString(NodeResult));

	return NodeResult;
}