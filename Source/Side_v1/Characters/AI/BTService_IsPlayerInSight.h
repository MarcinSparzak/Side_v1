// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_IsPlayerInSight.generated.h"

/**
 * 
 */
UCLASS()
class SIDE_V1_API UBTService_IsPlayerInSight : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_IsPlayerInSight();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
