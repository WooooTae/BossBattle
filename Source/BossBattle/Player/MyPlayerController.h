// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();
	
protected:
	virtual void BeginPlay() override;

protected:
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	TSubclassOf<class UUserWidget> CooldownWidgetClass;

	TSubclassOf<class UUserWidget> CooldownWidget2Class;

public:
	TObjectPtr<class UMyHPBarWidget> HUDWidget;

public:
	TObjectPtr<class UCooldownWidget> CooldownWidget;

public:
	TObjectPtr<class UCooldownWidget> CooldownWidget2;
};
