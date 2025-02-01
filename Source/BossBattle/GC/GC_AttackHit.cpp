// Fill out your copyright notice in the Description page of Project Settings.


#include "GC_AttackHit.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h" 
#include "Animation/AnimInstance.h"
#include "BossBattle/Character/CharacterBase.h"
#include "Kismet/GameplayStatics.h"

UGC_AttackHit::UGC_AttackHit()
{

}

bool UGC_AttackHit::OnExecute_Implementation(AActor* Target, const FGameplayCueParameters& Parameters) const
{
	const FHitResult* HitResult = Parameters.EffectContext.GetHitResult();
	if (HitResult)
	{
		if (NiagaraSystem)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(Target, NiagaraSystem, HitResult->ImpactPoint, HitResult->ImpactNormal.Rotation(), FVector(1.0f, 1.0f, 1.0f), true);
		}

		ACharacterBase* Character = Cast<ACharacterBase>(Target);
		if (Character)
		{
			UAnimInstance* AnimInstance =	Character->GetMesh()->GetAnimInstance();
			AnimInstance->Montage_Play(Character->GetHittedMontage());
		}

		return true;
	}
	else
	{
		for (const auto& TargetActor : Parameters.EffectContext.Get()->GetActors())
		{
			if (TargetActor.Get())
			{
				ACharacterBase* Character = Cast<ACharacterBase>(TargetActor.Get());
				if (Character)
				{
					UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
					AnimInstance->Montage_Play(Character->GetHittedMontage());
				}

				UNiagaraFunctionLibrary::SpawnSystemAtLocation(Target, NiagaraSystem, TargetActor.Get()->GetActorLocation(), FRotator::ZeroRotator, FVector(1.0f, 1.0f, 1.0f), true);
			}
		}

		return true;
	}

	return false;
}
