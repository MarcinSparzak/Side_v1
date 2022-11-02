// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
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

	ABaseEnemyAIController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UpdateCharacterWeaponAI(float WeaponRange);

	UPROPERTY(VisibleAnywhere, Category = AI)
		TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent = nullptr;
	TObjectPtr<class UAISenseConfig_Sight> AISenseConfigSight = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:

	UPROPERTY(EditAnywhere)
		UBehaviorTree* AIBehaviorTree;

	ABaseEnemyCharacter* EnemyCharacter;

	void SetupBlackboard();
	void SetupAIPerception();
	void UpdateSightRadius();

	UFUNCTION()
	void OnTargetPerceptionUpdatedDelegate(AActor* Actor, FAIStimulus Stimulus);
};
