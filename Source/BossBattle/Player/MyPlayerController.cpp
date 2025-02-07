// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "InputMappingContext.h"
#include "BossBattle/UI/MyHPBarWidget.h"
#include "BossBattle/UI/CooldownWidget.h"
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

	static ConstructorHelpers::FClassFinder<UUserWidget> CooldownWidgetRef(TEXT("/Game/BossBattle/Blueprint/UI/WBP_Cooldown.WBP_Cooldown_C"));
	{
		if (CooldownWidgetRef.Class)
		{
			CooldownWidgetClass = CooldownWidgetRef.Class;
		}
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> CooldownWidgetRef2(TEXT("/Game/BossBattle/Blueprint/UI/WBP_Cooldown2.WBP_Cooldown2_C"));
	{
		if (CooldownWidgetRef2.Class)
		{
			CooldownWidget2Class = CooldownWidgetRef2.Class;
		}
	}
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);

	HUDWidget = CreateWidget<UMyHPBarWidget>(this, HUDWidgetClass);
	CooldownWidget = CreateWidget<UCooldownWidget>(this, CooldownWidgetClass);
	CooldownWidget2 = CreateWidget<UCooldownWidget>(this, CooldownWidget2Class);
	if (HUDWidget)
	{
		HUDWidget->AddToViewport();
	}

	if (CooldownWidget)
	{
		CooldownWidget->AddToViewport();
	}

	if (CooldownWidget2)
	{
		CooldownWidget2->AddToViewport();
	}

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (PlayerCharacter && HUDWidget)
	{
		HUDWidget->ASC = PlayerCharacter->GetAbilitySystemComponent();
		HUDWidget->SetWidget();
	}
}
