// Fill out your copyright notice in the Description page of Project Settings.


#include "CooldownWidget.h"
#include "Components/ProgressBar.h"
#include "TimerManager.h"
#include "Abilities/GameplayAbility.h"

void UCooldownWidget::UpdateCooldown(UGameplayAbility* Skill)
{
    if (!Skill || !CooldownProgressBar)
    {
        return;
    }

    CurrentSkill = Skill;

    GetWorld()->GetTimerManager().ClearTimer(CooldownTimerHandle);

    // 0.1초마다 UpdateCooldownProgress 실행
    GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &UCooldownWidget::UpdateCooldownProgress, 0.1f, true);

    // 바로 한 번 UI 업데이트
    UpdateCooldownProgress();
}

void UCooldownWidget::UpdateCooldownProgress()
{
    if (!CooldownProgressBar || !CurrentSkill)
    {
        GetWorld()->GetTimerManager().ClearTimer(CooldownTimerHandle);
        return;
    }

    float CooldownTime = CurrentSkill->GetCooldownTimeRemaining();

    if (CooldownTime > 0)
    {
        // 남은 시간 / 전체 시간 비율 적용
        CooldownProgressBar->SetPercent(CooldownTime / 5.0f);
    }
    else
    {
        // 쿨다운 종료 -> 타이머 중지
        GetWorld()->GetTimerManager().ClearTimer(CooldownTimerHandle);
        CooldownProgressBar->SetPercent(100.0f);
    }
}
