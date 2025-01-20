// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Skill.h"
#include "AIController.h"
#include "BossBattle/Interface/NPCAIInterface.h"	
#include "BossBattle/Character/NonCharacterPlayer.h"

UBTTask_Skill::UBTTask_Skill()
{

}

EBTNodeResult::Type UBTTask_Skill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	APawn* ControllingPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	INPCAIInterface* AIPawn = Cast<INPCAIInterface>(ControllingPawn);
	if (nullptr == AIPawn)
	{
		return EBTNodeResult::Failed;
	}

	FAICharacterAttackFinished OnAttackFinished;

	OnAttackFinished.BindLambda(
		[&]()
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	);
	AIPawn->SetAIAttackDelegate(OnAttackFinished);
	AIPawn->AttackByAI(1);
	return EBTNodeResult::InProgress;
}
