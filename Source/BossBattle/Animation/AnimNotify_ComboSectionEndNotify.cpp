// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_ComboSectionEndNotify.h"
#include "BossBattle/Character/PlayerCharacter.h"
#include "AbilitySystemComponent.h"
#include "BossBattle/GA/GA_Attack.h"	
#include "BossBattle/Interface/ComboInterface.h"

void UAnimNotify_ComboSectionEndNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner()))
	{
		if (UAbilitySystemComponent* AbilitySystem = PlayerCharacter->GetAbilitySystemComponent())
		{
			for (const FGameplayAbilitySpec& Spec : AbilitySystem->GetActivatableAbilities())
			{
				IComboInterface* ComboAbility = Cast<IComboInterface>(Spec.GetPrimaryInstance());
				if (ComboAbility)
				{
					ComboAbility->OnComboSectionEnd();
				}
			}
		}
	}
}