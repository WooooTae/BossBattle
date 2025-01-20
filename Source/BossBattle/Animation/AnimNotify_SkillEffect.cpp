// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_SkillEffect.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h" 

void UAnimNotify_SkillEffect::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		AActor* Character = MeshComp->GetOwner();
		UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(Character,NiagaraSystem,Character->GetActorLocation() + FVector(0.0f, 0.0f, -100.0f),Character->GetActorRotation(), FVector(1.0f, 1.0f, 1.0f), true);
	}
}
