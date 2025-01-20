// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCSkillAttributeSet.h"

UNPCSkillAttributeSet::UNPCSkillAttributeSet() :
	SkillRange(500.0f),
	MaxSkillRange(1200.0f),
	SkillAttackRate(150.f),
	MaxSkillAttackRate(300.0f),
	SkillEnergy(100.0f),
	MaxSkillEnergy(100.0f)
{

}

void UNPCSkillAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetSkillRangeAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.1f, GetMaxSkillRange());
	}
	else if (Attribute == GetSkillAttackRateAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxSkillAttackRate());
	}
}
