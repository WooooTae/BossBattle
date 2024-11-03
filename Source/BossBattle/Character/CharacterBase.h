// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS()
class BOSSBATTLE_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacterBase();

	// Dead Section
protected:
	virtual void SetDead();
	void PlayDeadAnimation();

	float DeadEventDelayTime = 5.0f;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Stat,Meta=(PrivateAccess=true))
	TObjectPtr<class UAnimMontage> DeadMontage;

protected:
	UPROPERTY(VisibleAnywhere,BluePrintReadOnly,Category=Equiqment,Meta=(AllowPrivateAccess))
	TObjectPtr<class USkeletalMeshComponent> Weapon;
};
