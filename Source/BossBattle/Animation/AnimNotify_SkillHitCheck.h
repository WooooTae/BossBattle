// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTagContainer.h"
#include "AnimNotify_SkillHitCheck.generated.h"

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API UAnimNotify_SkillHitCheck : public UAnimNotify
{
	GENERATED_BODY()

public:
	UAnimNotify_SkillHitCheck();

protected:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere, Meta = (Categories = Event))
	FGameplayTag TriggerGameplayTag;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayCue)
	class UParticleSystem* ParticleSystem;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayCue)
	TObjectPtr<class UNiagaraSystem> NiagaraSystem;
};
