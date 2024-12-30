// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHPBarWidget.h"
#include "AbilitySystemComponent.h"
#include "BossBattle/AttributeSet/CharacterAttributeSet.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UMyHPBarWidget::SetAbilitySystemComponent(AActor* InOwner)
{
	Super::SetAbilitySystemComponent(InOwner);

	SetWidget();
}

void UMyHPBarWidget::OnHealthChanged(const FOnAttributeChangeData& ChangeData)
{
	CurrentHealth = ChangeData.NewValue;
	UpdateHpBar();
}

void UMyHPBarWidget::OnMaxHealthChanged(const FOnAttributeChangeData& ChangeData)
{
	CurrentMaxHealth = ChangeData.NewValue;
	UpdateHpBar();
}

void UMyHPBarWidget::SetWidget()
{
	if (ASC)
	{
		ASC->GetGameplayAttributeValueChangeDelegate(UCharacterAttributeSet::GetHealthAttribute()).AddUObject(this, &UMyHPBarWidget::OnHealthChanged);
		ASC->GetGameplayAttributeValueChangeDelegate(UCharacterAttributeSet::GetMaxHealthAttribute()).AddUObject(this, &UMyHPBarWidget::OnMaxHealthChanged);
		PbHpBar->SetFillColorAndOpacity(FLinearColor::Red);

		const UCharacterAttributeSet* CurrentAttributeSet = ASC->GetSet<UCharacterAttributeSet>();
		if (CurrentAttributeSet)
		{
			CurrentHealth = CurrentAttributeSet->GetHealth();
			CurrentMaxHealth = CurrentAttributeSet->GetMaxHealth();

			if (CurrentMaxHealth > 0.0f)
			{
				UpdateHpBar();
			}
		}
	}
}

void UMyHPBarWidget::UpdateHpBar()
{
	if (PbHpBar)
	{
		PbHpBar->SetPercent(CurrentHealth / CurrentMaxHealth);
	}

	if (TxtHpStat)
	{
		TxtHpStat->SetText(FText::FromString(FString::Printf(TEXT("%.0f/%.0f"),CurrentHealth,CurrentMaxHealth)));
	}
}
