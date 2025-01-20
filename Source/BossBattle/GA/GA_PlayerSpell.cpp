// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_PlayerSpell.h"
#include "BossBattle/Character/PlayerCharacter.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BossBattle/Prop/Fireball.h"

UGA_PlayerSpell::UGA_PlayerSpell()
{

}

void UGA_PlayerSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	APlayerCharacter* Target = Cast<APlayerCharacter>(ActorInfo->AvatarActor.Get());
	if (!Target)
	{
		return;
	}

	Target->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	SpellActionMontage = Target->GetSpellActionMontage();
	if (!SpellActionMontage)
	{
		return;
	}

	if (UWorld* World = GetWorld())
	{
		FVector SpawnLocation = Target->GetActorLocation() + Target->GetActorForwardVector();
		FRotator SpawnRotation = Target->GetActorRotation();

		AFireball* Fireball = World->SpawnActor<AFireball>(AFireball::StaticClass(), SpawnLocation, SpawnRotation);
		if (Fireball)
		{
			// 필요한 경우 추가 설정
			//Fireball->Speed = 1200.0f; // 파이어볼 속도 설정
		}
	}

	UAbilityTask_PlayMontageAndWait* PlayMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("SpellMontage"), SpellActionMontage, 1.0f);
	PlayMontageTask->OnCompleted.AddDynamic(this, &UGA_PlayerSpell::OnCompleteCallback);
	PlayMontageTask->OnInterrupted.AddDynamic(this, &UGA_PlayerSpell::OnInterruptedCallback);

	PlayMontageTask->ReadyForActivation();
}

void UGA_PlayerSpell::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	APlayerCharacter* Target = Cast<APlayerCharacter>(ActorInfo->AvatarActor.Get());
	if (!Target)
	{
		return;
	}

	Target->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_PlayerSpell::OnCompleteCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UGA_PlayerSpell::OnInterruptedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
