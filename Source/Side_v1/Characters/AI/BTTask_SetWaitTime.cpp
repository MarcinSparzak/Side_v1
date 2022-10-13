// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetWaitTime.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetWaitTime::UBTTask_SetWaitTime()
{
	NodeName = TEXT("Calculate Wait Time");
}

EBTNodeResult::Type UBTTask_SetWaitTime::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	float DefaultWaitTime = Blackboard->GetValueAsFloat(TEXT("DefaultWaitTime"));
	float RandomDeviation = Blackboard->GetValueAsFloat(TEXT("RandomDeviation"));

	DefaultWaitTime -= RandomDeviation;
	float result = DefaultWaitTime + FMath::RandRange(0.0f, 2 * RandomDeviation);

	Blackboard->SetValueAsFloat(GetSelectedBlackboardKey(), result);

	return EBTNodeResult::Type();
}
