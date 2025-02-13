// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "BossBattle/Player/MyPlayerController.h"

AMyGameModeBase::AMyGameModeBase()
{
	PlayerControllerClass = AMyPlayerController::StaticClass();

	static ConstructorHelpers::FClassFinder<UUserWidget> GameOverClassRef(TEXT("/Game/BossBattle/Blueprint/UI/WBP_GameOver.WBP_GameOver_C"));
	if (GameOverClassRef.Class)
	{
		GameOverClass = GameOverClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> GameEndClassRef(TEXT("/Game/BossBattle/Blueprint/UI/WBP_GameEnd.WBP_GameEnd_C"));
	if (GameEndClassRef.Class)
	{
		GameEndClass = GameEndClassRef.Class;
	}
}

void AMyGameModeBase::StartPlay()
{
	Super::StartPlay();
}

void AMyGameModeBase::BossGameOver()
{
	AMyPlayerController* PC = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this,0));
	if (PC && GameOverClass)
	{
		GameOverWidget = CreateWidget<UUserWidget>(PC,GameOverClass);
		if (GameOverWidget)
		{
			GameOverWidget->AddToViewport();

			PC->DisableInput(PC);
			PC->bShowMouseCursor = false;
		}
	}
}

void AMyGameModeBase::BossGameEnd()
{
	AMyPlayerController* PC = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PC && GameEndClass)
	{
		GameEndWidget = CreateWidget<UUserWidget>(PC, GameEndClass);
		if (GameEndWidget)
		{
			GameEndWidget->AddToViewport();

			PC->DisableInput(PC);
			PC->bShowMouseCursor = false;
		}
	}
}
