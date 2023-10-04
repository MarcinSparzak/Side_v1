// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindNextPathPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrolPath.h"
class UBlackboardKeyType_Object;

UBTTask_FindNextPathPoint::UBTTask_FindNextPathPoint()
{
    NodeName = TEXT("Find Next Path Point");
}

EBTNodeResult::Type UBTTask_FindNextPathPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
    APatrolPath* Path = Cast<APatrolPath>(Blackboard->GetValueAsObject(TEXT("Path")));

    if (Path != nullptr)
    {
        int index = Blackboard->GetValueAsInt(TEXT("PatrolPointIndex"));
        int length = Path->PathPoints.Num();
        if (index >= length)
        {
            index = 0;
        }

        FVector PathPoint = Path->PathPoints[index];
        FVector PathPointLocation = Path->GetActorLocation() + PathPoint;
        Blackboard->SetValueAsVector("NextPatrolPoint", PathPointLocation);

        ++index;
        Blackboard->SetValueAsInt("PatrolPointIndex", index);
    }

    return EBTNodeResult::Type();
}
