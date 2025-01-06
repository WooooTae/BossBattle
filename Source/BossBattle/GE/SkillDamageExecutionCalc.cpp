// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillDamageExecutionCalc.h"
#include "AbilitySystemComponent.h"
#include "BossBattle/AttributeSet/CharacterAttributeSet.h"
#include "BossBattle/AttributeSet/NPCSkillAttributeSet.h"

void USkillDamageExecutionCalc::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	if (SourceASC && TargetASC)
	{
		AActor* SourceActor = SourceASC->GetAvatarActor();
		AActor* TargetActor = TargetASC->GetAvatarActor();

		if (SourceActor && TargetActor)
		{
			const float MaxDamageRange = SourceASC->GetNumericAttributeBase(UNPCSkillAttributeSet::GetMaxSkillRangeAttribute());
			const float MaxDamage = SourceASC->GetNumericAttributeBase(UNPCSkillAttributeSet::GetMaxSkillAttackRateAttribute());
			const float Distance = FMath::Clamp(SourceActor->GetDistanceTo(TargetActor), 0.0f, MaxDamageRange);
			const float InvDamageRation = 1.0f - Distance / MaxDamageRange;
			float Damage = InvDamageRation * MaxDamage;

			OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UCharacterAttributeSet::GetDamageAttribute(), EGameplayModOp::Additive, Damage));
		}
	}
}
