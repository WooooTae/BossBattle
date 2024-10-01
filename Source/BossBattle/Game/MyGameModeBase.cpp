// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "BossBattle/Player/MyPlayerController.h"

AMyGameModeBase::AMyGameModeBase()
{
	PlayerControllerClass = AMyPlayerController::StaticClass();
}

void AMyGameModeBase::StartPlay()
{
	Super::StartPlay();
}
