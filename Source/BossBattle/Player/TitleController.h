// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TitleController.generated.h"

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API ATitleController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATitleController();

protected:
	virtual void BeginPlay() override;

	TSubclassOf<class UUserWidget> TitleWidgetClass;

public:
	TObjectPtr<class UTitleWidget> TitleWidget;
};
