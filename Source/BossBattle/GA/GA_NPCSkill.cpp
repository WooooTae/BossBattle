// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_NPCSkill.h"
#include "BossBattle/Character/NonCharacterPlayer.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/CharacterMovementComponent.h"

UGA_NPCSkill::UGA_NPCSkill()
{

}

void UGA_NPCSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle,ActorInfo,ActivationInfo,TriggerEventData);
	
	ANonCharacterPlayer* Target = Cast<ANonCharacterPlayer>(ActorInfo->AvatarActor.Get());
	if (!Target)
	{
		return;
	}

	Target->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);

	SkillActionMontage = Target->GetBasicSkillMontage();
	if (!SkillActionMontage)
	{
		return;
	}

	UAbilityTask_PlayMontageAndWait* PlayMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this,TEXT("SkillMontage"),SkillActionMontage,1.0f);
	PlayMontageTask->OnCompleted.AddDynamic(this,&UGA_NPCSkill::OnCompleteCallback);
	PlayMontageTask->OnInterrupted.AddDynamic(this,&UGA_NPCSkill::OnInterruptedCallback);

	PlayMontageTask->ReadyForActivation();
}

void UGA_NPCSkill::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	ANonCharacterPlayer* Target = Cast<ANonCharacterPlayer>(ActorInfo->AvatarActor.Get());
	if (!Target)
	{
		return;
	}

	Target->NotifyComboActionEnd();

	Target->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_NPCSkill::OnCompleteCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UGA_NPCSkill::OnInterruptedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
