// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TurnToTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BossBattle/Interface/NPCAIInterface.h"    

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
    NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp,NodeMemory);

    APawn* ControllingPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
    if (nullptr == ControllingPawn)
    {
        return EBTNodeResult::Failed;
    }

    APawn* TargetPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
    if (nullptr == TargetPawn)
    {
        return EBTNodeResult::Failed;
    }

    INPCAIInterface* AIPawn = Cast<INPCAIInterface>(ControllingPawn);
    if (nullptr == AIPawn)
    {
        return EBTNodeResult::Failed;
    }

    float TurnSpeed = AIPawn->GetAITurnSpeed();
    FVector LookVector = TargetPawn->GetActorLocation() - ControllingPawn->GetActorLocation();
    LookVector.Z = 0.0f;
    FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
    ControllingPawn->SetActorRotation(FMath::RInterpTo(ControllingPawn->K2_GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), TurnSpeed));;
    
    return EBTNodeResult::Succeeded;
}
