// Fill out your copyright notice in the Description page of Project Settings.


#include "CooldownBarWidget.h"
#include "Components/ProgressBar.h"
#include "AbilitySystemComponent.h"
#include "TimerManager.h"

void UCooldownBarWidget::SetAbilitySystemComponent(AActor* InOwner)
{
	Super::SetAbilitySystemComponent(InOwner);

	SetWidget();
}

void UCooldownBarWidget::SetWidget()
{

}

void UCooldownBarWidget::UpdateCooldown()
{
	FGameplayTagContainer CooldownTags;
	CooldownTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.State.SkillCoolDown")));

	TArray<FActiveGameplayEffectHandle> ActiveEffects = ASC->GetActiveEffects(
		FGameplayEffectQuery::MakeQuery_MatchAnyEffectTags(CooldownTags));

    float MaxTimeRemaining = 0.0f;

    for (const FActiveGameplayEffectHandle& Handle : ActiveEffects)
    {
        const FActiveGameplayEffect* ActiveEffect = ASC->GetActiveGameplayEffect(Handle);
        if (ActiveEffect)
        {
            float TimeRemaining = ActiveEffect->GetTimeRemaining(ASC->GetWorld()->GetTimeSeconds());
            MaxTimeRemaining = FMath::Max(MaxTimeRemaining, TimeRemaining);
        }
    }

    if (MaxTimeRemaining > 0)
    {
        // 예제: 총 쿨타임을 5초라고 가정 (실제 총 쿨타임 값은 GameplayEffect에서 설정한 Duration이나 별도 변수로 관리)
        CooldownProgressBar->SetPercent(MaxTimeRemaining / 5.0f);
    }
    else
    {
        // 쿨타임이 없으면 타이머 종료 및 퍼센트 0으로 설정
        if (UWorld* World = GetWorld())
        {
            World->GetTimerManager().ClearTimer(CooldownTimerHandle);
        }
        CooldownProgressBar->SetPercent(0.0f);
    }
}
