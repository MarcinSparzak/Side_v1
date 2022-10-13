// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SetWaitTime.generated.h"

/**
 * Wyznacznie czasu jaki postaæ ma czekaæ na punkcie patrolowym
 */
UCLASS()
class SIDE_V1_API UBTTask_SetWaitTime : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_SetWaitTime();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	
};
