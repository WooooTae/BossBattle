// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_PlayerSpell.generated.h"

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API UGA_PlayerSpell : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_PlayerSpell();

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	UFUNCTION()
	void OnCompleteCallback();

	UFUNCTION()
	void OnInterruptedCallback();

public:
	UPROPERTY()
	TObjectPtr<class UAnimMontage> SpellActionMontage;
};
