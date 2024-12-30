// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUDWidget.h"
#include "BossBattle/UI/MyHPBarWidget.h"

UMyHUDWidget::UMyHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UMyHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpBar = Cast<UMyHPBarWidget>(GetWidgetFromName(TEXT("WBP_HpBar")));
	ensure(HpBar);
}

void UMyHUDWidget::UpdateHpBar()
{
	HpBar->UpdateHpBar();
}
