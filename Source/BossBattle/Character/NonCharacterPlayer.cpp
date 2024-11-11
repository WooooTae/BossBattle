// Fill out your copyright notice in the Description page of Project Settings.


#include "NonCharacterPlayer.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"

ANonCharacterPlayer::ANonCharacterPlayer()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> NPCMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Plladin_RootBone/Maw_J_Laygo.Maw_J_Laygo'"));
	if (NPCMeshRef.Object)
	{
		NPCMesh = NPCMeshRef.Object;
	}
	GetMesh()->SetHiddenInGame(true);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 350.0f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;
}

void ANonCharacterPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	NPCMeshHandle = UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(NPCMesh,FStreamableDelegate::CreateUObject(this,&ANonCharacterPlayer::NPCMeshLoadComplete));
}

void ANonCharacterPlayer::SetDead()
{
   Super::SetDead();

   FTimerHandle DeadTimeHandle;
   GetWorld()->GetTimerManager().SetTimer(DeadTimeHandle, FTimerDelegate::CreateLambda(
	   [&]()
	   {
		   Destroy();
	   }
   ),DeadEventDelayTime,false);
}

void ANonCharacterPlayer::NPCMeshLoadComplete()
{
	if (NPCMeshHandle.IsValid())
	{
		USkeletalMesh* NpcMesh = Cast<USkeletalMesh>(NPCMeshHandle->GetLoadedAsset());
		if (NpcMesh)
		{
			GetMesh()->SetSkeletalMesh(NpcMesh);
			GetMesh()->SetHiddenInGame(false);
		}
	}

	NPCMeshHandle->ReleaseHandle(); 
}
float ANonCharacterPlayer::GetAIPatrolRadius()
{
	return 800.0f;
}

float ANonCharacterPlayer::GetAIDetectRange()
{
	return 100.0f;
}

float ANonCharacterPlayer::GetAIAttackRange()
{
	return 0.0f;
}

float ANonCharacterPlayer::GetAITurnSpeed()
{
	return 2.0f;
}

void ANonCharacterPlayer::SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished)
{

}

void ANonCharacterPlayer::AttackByAI()
{

}

