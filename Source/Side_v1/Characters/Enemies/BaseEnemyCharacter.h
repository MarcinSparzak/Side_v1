// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseCharacter.h"
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

	UPROPERTY(EditInstanceOnly, meta = (EditCondition = "IsPatrolling", Category="AI|Patrolling"))
	APatrolPath* PatrolPath;

	UPROPERTY(EditInstanceOnly, meta = (EditCondition = "IsPatrolling", Category = "AI|Patrolling"))
	float DefaultWaitTime = 0.0f;

	UPROPERTY(EditInstanceOnly, meta = (EditCondition = "IsPatrolling", Category = "AI|Patrolling"))
	float RandomDeviation = 0.0f;

	UPROPERTY(EditDefaultsOnly, meta = (Category = "AI|Combat"))
	float SightRadius = 2000;
	UPROPERTY(EditDefaultsOnly, meta = (Category = "AI|Combat"))
	float LoseSightRadius = 2500;


	UFUNCTION()
	void BaseAttack(FVector TargetPoint);

	virtual void Death() override;

protected:
	virtual void BeginPlay() override;

};
