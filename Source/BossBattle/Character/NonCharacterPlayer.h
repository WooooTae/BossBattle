// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "Engine/StreamableManager.h"
#include "BossBattle/Interface/NPCAIInterface.h"
#include "NonCharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API ANonCharacterPlayer : public ACharacterBase,public INPCAIInterface
{
	GENERATED_BODY()
	
public:
	ANonCharacterPlayer();

protected:
	virtual void PostInitializeComponents() override;
	virtual void SetDead() override;

protected:
	void NPCMeshLoadComplete();

	FSoftObjectPath NPCMesh;

	TSharedPtr<FStreamableHandle> NPCMeshHandle;

	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAITurnSpeed() override;

	virtual void SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished) override;
	virtual void AttackByAI() override;

	FAICharacterAttackFinished OnAttackFinished;
};
