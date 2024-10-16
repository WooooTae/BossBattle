// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Roll.h"
#include "BossBattle/Character/PlayerCharacter.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

UGA_Roll::UGA_Roll()
{
	
}

void UGA_Roll::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle,ActorInfo,ActivationInfo,TriggerEventData);

	APlayerCharacter* TargetCharacter = Cast<APlayerCharacter>(ActorInfo->AvatarActor.Get());
	if (!TargetCharacter)
	{
		return;
	}

	RollActionMontage = TargetCharacter->GetRollActionMontage();
	if (!RollActionMontage)
	{
		return;
	}

	UAbilityTask_PlayMontageAndWait* PlayMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this,TEXT("RollMontage"),RollActionMontage,1.0f);
	PlayMontageTask->OnCompleted.AddDynamic(this,&UGA_Roll::OnCompleteCallback);
	PlayMontageTask->OnInterrupted.AddDynamic(this, &UGA_Roll::OnInterruptedCallback);

	PlayMontageTask->ReadyForActivation();
}

void UGA_Roll::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle,ActorInfo,ActivationInfo,bReplicateEndAbility,bWasCancelled);
}

void UGA_Roll::OnCompleteCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,bReplicatedEndAbility,bWasCancelled);
}

void UGA_Roll::OnInterruptedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
