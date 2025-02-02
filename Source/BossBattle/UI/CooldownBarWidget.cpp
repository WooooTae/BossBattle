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
        // ����: �� ��Ÿ���� 5�ʶ�� ���� (���� �� ��Ÿ�� ���� GameplayEffect���� ������ Duration�̳� ���� ������ ����)
        CooldownProgressBar->SetPercent(MaxTimeRemaining / 5.0f);
    }
    else
    {
        // ��Ÿ���� ������ Ÿ�̸� ���� �� �ۼ�Ʈ 0���� ����
        if (UWorld* World = GetWorld())
        {
            World->GetTimerManager().ClearTimer(CooldownTimerHandle);
        }
        CooldownProgressBar->SetPercent(0.0f);
    }
}
