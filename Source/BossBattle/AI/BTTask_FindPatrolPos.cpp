// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPatrolPos.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BossBattle/Interface/NPCAIInterface.h"

UBTTask_FindPatrolPos::UBTTask_FindPatrolPos()
{

}

EBTNodeResult::Type UBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
   EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp,NodeMemory);

   APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
   if (nullptr == ControllingPawn)
   {
       return EBTNodeResult::Failed;
   }

   UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
   if (nullptr == NavSystem)
   {
       return EBTNodeResult::Failed;
   }

   INPCAIInterface* AIPawn = Cast<INPCAIInterface>(ControllingPawn);
   if (nullptr == AIPawn)
   {
       return EBTNodeResult::Failed;
   }

   FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("HomePos"));
   float PatrolRadius = AIPawn->GetAIPatrolRadius();
   FNavLocation NextPatrolPos;

   if (NavSystem->GetRandomPointInNavigableRadius(Origin, PatrolRadius, NextPatrolPos))
   {
       OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolPos"),NextPatrolPos.Location);
       return EBTNodeResult::Succeeded;
   }
    return EBTNodeResult::Failed;
}
