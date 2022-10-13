// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseEnemyAIController.generated.h"
class ABaseEnemyCharacter;
/**
 * 
 */
UCLASS()
class SIDE_V1_API ABaseEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:

	UPROPERTY(EditAnywhere)
		UBehaviorTree* AIBehaviorTree;

	ABaseEnemyCharacter* EnemyCharacter;
};
