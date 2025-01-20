// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_SkillCollDown.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AbilitySystemComponent.h"

UBTDecorator_SkillCollDown::UBTDecorator_SkillCollDown()
{
	NodeName = TEXT("IsCoolDown");
}

bool UBTDecorator_SkillCollDown::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return false;
	}

	UAbilitySystemComponent* ASC = ControllingPawn->FindComponentByClass<UAbilitySystemComponent>();
	if (!ASC)
	{
		return false;
	}

	FGameplayTag CooldownTag = FGameplayTag::RequestGameplayTag(FName("Character.State.SkillCoolDown"));

	if (ASC->HasMatchingGameplayTag(CooldownTag))
	{
		UE_LOG(LogTemp,Log,TEXT("SkillCoolDown"));
		return true;
	}


	return false;
}
