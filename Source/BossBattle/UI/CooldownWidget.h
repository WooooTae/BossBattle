// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "CooldownWidget.generated.h"

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API UCooldownWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UPROPERTY(meta = (BindWidget))
    UProgressBar* CooldownProgressBar;

    void UpdateCooldown(class UGameplayAbility* Skill);

    void UpdateCooldownProgress();

private:
    FTimerHandle CooldownTimerHandle;

    UGameplayAbility* CurrentSkill;
};
