// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "InputMappingContext.h"
#include "BossBattle/UI/MyHPBarWidget.h"
#include "BossBattle/Character/PlayerCharacter.h"
#include "AbilitySystemComponent.h"

AMyPlayerController::AMyPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> HUDWidgetRef(TEXT("/Game/BossBattle/Blueprint/UI/WBP_HUDHpBar.WBP_HUDHpBar_C"));
	{
		if (HUDWidgetRef.Class)
		{
			HUDWidgetClass = HUDWidgetRef.Class; 
		}
	}
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);

	HUDWidget = CreateWidget<UMyHPBarWidget>(this, HUDWidgetClass);
	if (HUDWidget)
	{
		HUDWidget->AddToViewport();
	}

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (PlayerCharacter && HUDWidget)
	{
		HUDWidget->ASC = PlayerCharacter->GetAbilitySystemComponent();
		HUDWidget->SetWidget();
	}
}
