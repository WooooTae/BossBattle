// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API UMyHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UMyHUDWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	void UpdateHpBar();

protected:
	UPROPERTY()
	TObjectPtr<class UMyHPBarWidget> HpBar;
};
