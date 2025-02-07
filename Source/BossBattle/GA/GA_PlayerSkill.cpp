// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_PlayerSkill.h"
#include "BossBattle/Character/PlayerCharacter.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "BossBattle/UI/CooldownWidget.h"
#include "BossBattle/Player/MyPlayerController.h"

UGA_PlayerSkill::UGA_PlayerSkill()
{
	static ConstructorHelpers::FClassFinder<UGameplayEffect> CooldownClassRef(TEXT("/Game/BossBattle/Blueprint/GE/BPGE_Cooldown2.BPGE_Cooldown2_C"));
	if (CooldownClassRef.Class)
	{
		CooldownGameplayEffectClass = CooldownClassRef.Class;
	}
}

void UGA_PlayerSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AMyPlayerController* PC = Cast<AMyPlayerController>(ActorInfo->PlayerController);

	UCooldownWidget* MyCool = PC->CooldownWidget2;

	if (MyCool)
	{
		MyCool->UpdateCooldown(this);
	}

	APlayerCharacter* Target = Cast<APlayerCharacter>(ActorInfo->AvatarActor.Get());
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

	UAbilityTask_PlayMontageAndWait* PlayMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("SkillMontage"), SkillActionMontage, 1.0f);
	PlayMontageTask->OnCompleted.AddDynamic(this, &UGA_PlayerSkill::OnCompleteCallback);
	PlayMontageTask->OnInterrupted.AddDynamic(this, &UGA_PlayerSkill::OnInterruptedCallback);

	PlayMontageTask->ReadyForActivation();
}

void UGA_PlayerSkill::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	APlayerCharacter* Target = Cast<APlayerCharacter>(ActorInfo->AvatarActor.Get());
	if (!Target)
	{
		return;
	}

	Target->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_PlayerSkill::OnCompleteCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UGA_PlayerSkill::OnInterruptedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
