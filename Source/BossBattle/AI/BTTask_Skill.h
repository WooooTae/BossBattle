// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Skill.generated.h"

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API UBTTask_Skill : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_Skill();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
