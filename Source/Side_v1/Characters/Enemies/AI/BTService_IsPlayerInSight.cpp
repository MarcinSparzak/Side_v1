// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsPlayerInSight.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTService_IsPlayerInSight::UBTService_IsPlayerInSight()
{
	NodeName = "Check For Player In Sight";
}

void UBTService_IsPlayerInSight::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* PawnController = OwnerComp.GetAIOwner();
	if (PawnController != nullptr)
	{
		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		if (PawnController->LineOfSightTo(PlayerPawn))
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("IsPlayerInAttackRange"), false);
		}
	}
	return;
}
