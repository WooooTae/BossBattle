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

    // 0.1�ʸ��� UpdateCooldownProgress ����
    GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &UCooldownWidget::UpdateCooldownProgress, 0.1f, true);

    // �ٷ� �� �� UI ������Ʈ
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
        // ���� �ð� / ��ü �ð� ���� ����
        CooldownProgressBar->SetPercent(CooldownTime / 5.0f);
    }
    else
    {
        // ��ٿ� ���� -> Ÿ�̸� ����
        GetWorld()->GetTimerManager().ClearTimer(CooldownTimerHandle);
        CooldownProgressBar->SetPercent(100.0f);
    }
}
