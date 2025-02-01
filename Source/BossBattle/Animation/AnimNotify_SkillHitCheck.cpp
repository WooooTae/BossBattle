// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_SkillHitCheck.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h" 

UAnimNotify_SkillHitCheck::UAnimNotify_SkillHitCheck()
{

}

FString UAnimNotify_SkillHitCheck::GetNotifyName_Implementation() const
{
	return TEXT("SkillHitCheck");
}

void UAnimNotify_SkillHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		AActor* OwnerActor = MeshComp->GetOwner();
		if (OwnerActor)
		{
			AActor* Character = MeshComp->GetOwner();
			FGameplayEventData PayloadData;
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, TriggerGameplayTag, PayloadData);
			UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(Character, NiagaraSystem, Character->GetActorLocation() + FVector(0.0f, 0.0f, + 50.0f), Character->GetActorRotation(), FVector(1.0f, 1.0f, 1.0f), true);
		}
	}
}
