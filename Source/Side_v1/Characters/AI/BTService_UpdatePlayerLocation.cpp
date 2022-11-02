// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdatePlayerLocation.h"
#include "../PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

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
	UE_LOG(LogTemp, Warning, TEXT("Player Location Updated"));
	AIBlackboard->SetValueAsVector(TEXT("PlayerLocation"), TargetLocation);

}
