// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

//UTitleWidget::UTitleWidget()
//{
//
//}

void UTitleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	NewGameButton.Get()->OnClicked.AddDynamic(this,&ThisClass::OnNewGamButtonClicked);
	ExitGameButton.Get()->OnClicked.AddDynamic(this,&ThisClass::OnExitGameButtonClicked);
}

void UTitleWidget::OnNewGamButtonClicked()
{
	UE_LOG(LogTemp,Log,TEXT("Button Clicked"));
	UGameplayStatics::OpenLevel(GetWorld(),FName(TEXT("Stage")),true);
}

void UTitleWidget::OnExitGameButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this,GetOwningPlayer(),EQuitPreference::Quit,false);
}
