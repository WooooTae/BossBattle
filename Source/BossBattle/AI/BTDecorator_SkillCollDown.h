// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_SkillCollDown.generated.h"

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API UBTDecorator_SkillCollDown : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_SkillCollDown();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
