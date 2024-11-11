// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

ANPCAIController::ANPCAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(TEXT("/Script/AIModule.BlackboardData'/Game/BossBattle/Blueprint/AI/BB_NPC.BB_NPC'"));
	if (BBAssetRef.Object)
	{
		BBAsset = BBAssetRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Script/AIModule.BehaviorTree'/Game/BossBattle/Blueprint/AI/BT_NPC.BT_NPC'"));
	if (BTAssetRef.Object)
	{
		BTAsset = BTAssetRef.Object;
	}
}

void ANPCAIController::RunAI()
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();
	if (UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsVector(TEXT("HomePos"),GetPawn()->GetActorLocation());

		bool RunResult = RunBehaviorTree(BTAsset);
		ensure(RunResult);
	}
}

void ANPCAIController::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComponent)
	{
		BTComponent->StopTree();
	}
}

void ANPCAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();
}
