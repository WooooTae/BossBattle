// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "Engine/StreamableManager.h"
#include "NonCharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API ANonCharacterPlayer : public ACharacterBase
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
};
