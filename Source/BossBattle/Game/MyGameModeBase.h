// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMyGameModeBase();

	virtual void StartPlay() override;

	UFUNCTION()
	void BossGameOver();

	UFUNCTION()
	void BossGameEnd();

public:
	TSubclassOf<class UUserWidget> GameOverClass;

	TSubclassOf<class UUserWidget> GameEndClass;

	UUserWidget* GameOverWidget;

	UUserWidget* GameEndWidget;
};
