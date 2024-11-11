// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BossBattle/Interface/NPCAIInterface.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp,NodeMemory,DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return;
	}

	FVector Center = ControllingPawn->GetActorLocation();
	UWorld* World = ControllingPawn->GetWorld();
	if (nullptr == World)
	{
		return;
	}

	INPCAIInterface* AIPawn = Cast<INPCAIInterface>(ControllingPawn);
	if (nullptr == AIPawn)
	{
		return;
	}
	
	float DetectRadius = AIPawn->GetAIDetectRange();

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParms(SCENE_QUERY_STAT(Detect),false,ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParms
	);

	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			APawn* Pawn = Cast<APawn>(OverlapResult.GetActor());
			if (Pawn && Pawn->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"),Pawn);
				return;
			}
		}
	}
	
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"),nullptr);
}
