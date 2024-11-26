// Fill out your copyright notice in the Description page of Project Settings.


#include "NonCharacterPlayer.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "Animation/AnimInstance.h"
#include "BossBattle/AttributeSet/CharacterAttributeSet.h"

ANonCharacterPlayer::ANonCharacterPlayer()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	AttributrSet = CreateDefaultSubobject<UCharacterAttributeSet>(TEXT("AttributeSet"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> NPCMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Plladin_RootBone/Maw_J_Laygo.Maw_J_Laygo'"));
	if (NPCMeshRef.Object)
	{
		NPCMesh = NPCMeshRef.Object;
	}
	GetMesh()->SetHiddenInGame(true);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
}

void ANonCharacterPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	for (const auto& StartAbility : StartAbilities)
	{
		FGameplayAbilitySpec StartSpec(StartAbility);
		ASC->GiveAbility(StartSpec);
	}

	for (const auto& StartInputAbility : StartInputAbilities)
	{
		FGameplayAbilitySpec StartSpec(StartInputAbility.Value);
		StartSpec.InputID = StartInputAbility.Key;
		ASC->GiveAbility(StartSpec);
	}

	ASC->InitAbilityActorInfo(this, this);
	AttributrSet->OnOutOfHealth.AddDynamic(this, &ThisClass::OnOutOfHealth);

	//FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
	//EffectContextHandle.AddSourceObject(this);
	//FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec()
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
	return 400.0f;
}

float ANonCharacterPlayer::GetAIAttackRange()
{
	return 100.0f;
}

float ANonCharacterPlayer::GetAITurnSpeed()
{
	return 2.0f;
}

void ANonCharacterPlayer::SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished)
{
	OnAttackFinished = InOnAttackFinished;
}

void ANonCharacterPlayer::GASInputPressed(int32 InputId)
{
	FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(InputId);
	if (Spec)
	{
		Spec->InputPressed = true;
		if (Spec->IsActive())
		{
			ASC->AbilitySpecInputPressed(*Spec);
		}
		else
		{
			ASC->TryActivateAbility(Spec->Handle);
		}
	}
}

void ANonCharacterPlayer::GASInputReleased(int32 InputId)
{
	FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(InputId);
	if (Spec)
	{
		Spec->InputPressed = false;
		if (Spec->IsActive())
		{
			ASC->AbilitySpecInputReleased(*Spec);
		}
	}
}

void ANonCharacterPlayer::AttackByAI()
{
	//GASInputPressed(0);

	UAnimInstance* Anim = GetMesh()->GetAnimInstance();
	if (Anim)
	{
		Anim->Montage_Play(ComboActionMontage,1.0f);
	}
}

void ANonCharacterPlayer::NotifyComboActionEnd()
{
	OnAttackFinished.ExecuteIfBound();
}

void ANonCharacterPlayer::OnOutOfHealth()
{
	SetDead();
}

