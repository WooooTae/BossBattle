// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleController.h"
#include "BossBattle/Player/TitleController.h"
#include "BossBattle/UI/TitleWidget.h"


ATitleController::ATitleController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> TitleWidgetRef(TEXT("/Game/BossBattle/Blueprint/UI/WBP_Title.WBP_Title_C"));
	{
		if (TitleWidgetRef.Class)
		{
			TitleWidgetClass = TitleWidgetRef.Class;
		}
	}
}

void ATitleController::BeginPlay()
{
	Super::BeginPlay();

	TitleWidget = CreateWidget<UTitleWidget>(this, TitleWidgetClass);
	if (TitleWidget)
	{
		TitleWidget->AddToViewport();
		FInputModeGameAndUI GameAndUIInputMode;
		GameAndUIInputMode.SetWidgetToFocus(TitleWidget->TakeWidget());
		GameAndUIInputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(GameAndUIInputMode);
		bShowMouseCursor = true;
	}
}
