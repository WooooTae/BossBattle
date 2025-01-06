// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_Falling.h"
#include "BossBattle/Character/NonCharacterPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAnimNotify_Falling::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (ANonCharacterPlayer* NPC = Cast<ANonCharacterPlayer>(MeshComp->GetOwner()))
	{
		NPC->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
	}
}
