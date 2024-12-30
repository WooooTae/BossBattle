// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyUserWidget.h"
#include "GameplayEffectTypes.h"
#include "MyHPBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API UMyHPBarWidget : public UMyUserWidget
{
	GENERATED_BODY()

protected:
	virtual void SetAbilitySystemComponent(AActor* InOwner) override;

	virtual void OnHealthChanged(const FOnAttributeChangeData& ChangeData);
	virtual void OnMaxHealthChanged(const FOnAttributeChangeData& ChangeData);

public:
	void SetWidget();

	void UpdateHpBar();

protected:
	UPROPERTY(Meta=(BindWidget))
	TObjectPtr<class UProgressBar> PbHpBar;

	UPROPERTY(Meta=(BindWidget))
	TObjectPtr<class UTextBlock> TxtHpStat;

	float CurrentHealth = 0.0f;
	float CurrentMaxHealth = 0.1f;
};
