// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdatePlayerLocation.h"
#include "../PlayerCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_UpdatePlayerLocation::UBTService_UpdatePlayerLocation()
{
	NodeName = "Update Player Location";
}

void UBTService_UpdatePlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* AIBlackboard = OwnerComp.GetBlackboardComponent();
	if (AIBlackboard == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No blackboard"));
		return;
	}

	APlayerCharacter* Target = Cast<APlayerCharacter>(AIBlackboard->GetValueAsObject(TEXT("Player")));
	if (Target == nullptr) 
	{
		UE_LOG(LogTemp, Warning, TEXT("No Target"));
		return;
	}

	FVector TargetLocation = Target->GetActorLocation();
	//UE_LOG(LogTemp, Warning, TEXT("Player Location Updated"));
	AIBlackboard->SetValueAsVector(TEXT("PlayerLocation"), TargetLocation);
	AIBlackboard->SetValueAsBool(TEXT("IsMoveToPlayerPossible"), true);


	/*
		Establish if player is in range of attack
	*/
	FVector OwnerLocation = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
	float Distance = FVector::Dist(OwnerLocation, TargetLocation);
	//UE_LOG(LogTemp, Warning, TEXT("Distance %f"), Distance);
	if (Distance >= AIBlackboard->GetValueAsFloat(TEXT("WeaponRange")))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Player Out of Range"));
		AIBlackboard->SetValueAsBool(TEXT("IsPlayerInAttackRange"), false);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Player in Range"));
		AIBlackboard->SetValueAsBool(TEXT("IsPlayerInAttackRange"), true);
	}
}
