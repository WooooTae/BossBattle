// Fill out your copyright notice in the Description page of Project Settings.


#include "NonCharacterPlayer.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "Animation/AnimInstance.h"
#include "BossBattle/AttributeSet/CharacterAttributeSet.h"
#include "BossBattle/AttributeSet/NPCSkillAttributeSet.h"
#include "BossBattle/UI/MyWidgetComponent.h"
#include "BossBattle/UI/MyUserWidget.h"

ANonCharacterPlayer::ANonCharacterPlayer()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	AttributrSet = CreateDefaultSubobject<UCharacterAttributeSet>(TEXT("AttributeSet"));
	SkillAttributeSet = CreateDefaultSubobject<UNPCSkillAttributeSet>(TEXT("SkillAttributeSet"));

	HpBar = CreateDefaultSubobject<UMyWidgetComponent>(TEXT("Widget"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.0f,0.0f,250.0f));

	static ConstructorHelpers::FClassFinder<UUserWidget> HpBarWidgetRef(TEXT("/Game/BossBattle/Blueprint/UI/WBP_HpBar.WBP_HpBar_C"));
	if (HpBarWidgetRef.Class)
	{
		HpBar->SetWidgetClass(HpBarWidgetRef.Class);
		HpBar->SetWidgetSpace(EWidgetSpace::Screen);
		HpBar->SetDrawSize(FVector2D(300.0f,30.0f));
		HpBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> NPCMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Plladin_RootBone/Maw_J_Laygo_root.Maw_J_Laygo_root'"));
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
	return  AttributrSet->GetAttackRange() + AttributrSet->GetAttackRadius() * 2;
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
	if (ASC)
	{
		GetCharacterMovement()->MovementMode = EMovementMode::MOVE_None;

		FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(0);
		if (Spec)
		{
			if (Spec->IsActive())
			{
				Spec->InputPressed = true;
				ASC->AbilitySpecInputPressed(*Spec);
			}
			else
			{
				Spec->InputPressed = true;
				ASC->TryActivateAbility(Spec->Handle);
			}
		}

		//GASInputPressed(0);
	}
}

void ANonCharacterPlayer::OnOutOfHealth()
{
	SetDead();
}

