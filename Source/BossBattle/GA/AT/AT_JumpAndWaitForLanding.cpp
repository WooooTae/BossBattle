// Fill out your copyright notice in the Description page of Project Settings.


#include "AT_JumpAndWaitForLanding.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BossBattle/Character/PlayerCharacter.h"

UAT_JumpAndWaitForLanding::UAT_JumpAndWaitForLanding()
{

}

UAT_JumpAndWaitForLanding* UAT_JumpAndWaitForLanding::CreateTask(UGameplayAbility* OwningAbility)
{
	UAT_JumpAndWaitForLanding* NewTask = NewAbilityTask<UAT_JumpAndWaitForLanding>(OwningAbility);
	return NewTask;
}

void UAT_JumpAndWaitForLanding::Activate()
{
	Super::Activate();

	APlayerCharacter* Character = CastChecked<APlayerCharacter>(GetAvatarActor());
	JumpActionMontage = Character->GetJumpActionMontage();
	Character->LandedDelegate.AddDynamic(this,&UAT_JumpAndWaitForLanding::OnLandedCallback);

	Character->Jump();
}

void UAT_JumpAndWaitForLanding::OnDestroy(bool AbilityEnded)
{
	ACharacter* Character = CastChecked<ACharacter>(GetAvatarActor());
	Character->LandedDelegate.RemoveDynamic(this,&UAT_JumpAndWaitForLanding::OnLandedCallback);

	Super::OnDestroy(AbilityEnded);
}

void UAT_JumpAndWaitForLanding::OnLandedCallback(const FHitResult& Hit)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnComplete.Broadcast();
	}
}
