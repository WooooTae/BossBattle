// Fill out your copyright notice in the Description page of Project Settings.


#include "TA_SphereTrace.h"
#include "BossBattle/Character/CharacterBase.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "DrawDebugHelpers.h"
#include "BossBattle/AttributeSet/NPCSkillAttributeSet.h"

FGameplayAbilityTargetDataHandle ATA_SphereTrace::MakeTargetData() const
{
	ACharacterBase* Character = CastChecked<ACharacterBase>(SourceActor);
	
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(SourceActor);

	if (!ASC)
	{
		return FGameplayAbilityTargetDataHandle();
	}

	const UNPCSkillAttributeSet* SkillAttribute = ASC->GetSet<UNPCSkillAttributeSet>();

	if (!SkillAttribute)
	{
		return FGameplayAbilityTargetDataHandle();
	}

	TArray<FOverlapResult> Overlaps;
	const float SkillRadius = SkillAttribute->GetSkillRange();

	const FVector Origin = Character->GetActorLocation();

	FCollisionQueryParams Params(FName(TEXT("SkillRadius")), false, Character);
	GetWorld()->OverlapMultiByChannel(
		Overlaps,
		Origin,
		FQuat::Identity,
		ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(SkillRadius), Params);

	TArray<TWeakObjectPtr<AActor>> HitActors;
	for (const FOverlapResult& Overlap : Overlaps)
	{
		AActor* HitActor = Overlap.OverlapObjectHandle.FetchActor<AActor>();
		if (HitActor && !HitActors.Contains(HitActor))
		{
			HitActors.Add(HitActor);
		}
	}

	FGameplayAbilityTargetData_ActorArray* ActorsData = new FGameplayAbilityTargetData_ActorArray();
	ActorsData->SetActors(HitActors);
#if ENABLE_DRAW_DEBUG

		if (bShowDebug)
		{
			FColor DrawColor = HitActors.Num() > 0 ? FColor::Green : FColor::Red;
			DrawDebugSphere(GetWorld(), Origin, SkillRadius, 16, DrawColor, false, 5.0f);
		}
#endif
	return FGameplayAbilityTargetDataHandle(ActorsData);
}
