// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyUserWidget.h"
#include "CooldownBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API UCooldownBarWidget : public UMyUserWidget
{
	GENERATED_BODY()

protected:
    virtual void SetAbilitySystemComponent(AActor* InOwner) override;

protected:
    UPROPERTY(Meta = (BindWidget))
    TObjectPtr<class UProgressBar>  CooldownProgressBar;

public:
    void SetWidget();

    void UpdateCooldown();

private:
    FTimerHandle CooldownTimerHandle;
};
