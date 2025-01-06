// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "TA_SkillRadius.generated.h"

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API ATA_SkillRadius : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
	
public:
	ATA_SkillRadius();

	virtual void StartTargeting(UGameplayAbility* Ability) override;

	virtual void ConfirmTargetingAndContinue() override;

protected:
	virtual FGameplayAbilityTargetDataHandle MakeTargetData() const;
};