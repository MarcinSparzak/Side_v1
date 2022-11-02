// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_MoveToWithCustomRadius.generated.h"

/**
 * 
 */
UCLASS()
class SIDE_V1_API UBTTask_MoveToWithCustomRadius : public UBTTask_MoveTo
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
public:
	UBTTask_MoveToWithCustomRadius();

	
};
