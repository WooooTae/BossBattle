// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySystemInterface.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API UMyUserWidget : public UUserWidget, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	virtual void SetAbilitySystemComponent(AActor* InOwner);
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

public:
	UPROPERTY(EditAnywhere,Category=GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;
};
