// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "BaseEnemyCharacter.generated.h"
class APatrolPath;
/**
 * 
 */
UCLASS()
class SIDE_V1_API ABaseEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:

	ABaseEnemyCharacter();

	UPROPERTY(EditInstanceOnly, Category = "AI|Patrolling")
	bool IsPatrolling;

	UPROPERTY(EditInstanceOnly, meta = (EditCondition = "IsPatrolling"), Category="AI|Patrolling")
	APatrolPath* PatrolPath;

	UPROPERTY(EditInstanceOnly, meta = (EditCondition = "IsPatrolling"), Category = "AI|Patrolling")
	float DefaultWaitTime = 0.0f;

	UPROPERTY(EditInstanceOnly, meta = (EditCondition = "IsPatrolling"), Category = "AI|Patrolling")
	float RandomDeviation = 0.0f;
};
