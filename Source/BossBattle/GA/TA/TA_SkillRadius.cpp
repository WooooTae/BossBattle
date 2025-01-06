// Fill out your copyright notice in the Description page of Project Settings.


#include "TA_SkillRadius.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "BossBattle/Character/CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"

ATA_SkillRadius::ATA_SkillRadius()
{

}

void ATA_SkillRadius::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);

	SourceActor = Ability->GetCurrentActorInfo()->AvatarActor.Get();
}

void ATA_SkillRadius::ConfirmTargetingAndContinue()
{
	if (SourceActor)
	{
		FGameplayAbilityTargetDataHandle DataHandle = MakeTargetData();
		TargetDataReadyDelegate.Broadcast(DataHandle);
	}
}

FGameplayAbilityTargetDataHandle ATA_SkillRadius::MakeTargetData() const
{
	ACharacterBase* Character = CastChecked<ACharacterBase>(SourceActor);

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(SourceActor);
	if (!ASC)
	{
		return FGameplayAbilityTargetDataHandle();
	}

	TArray<FOverlapResult> Overlaps;
	const float SkillRadius = 50.0f;

	const FVector Origin = Character->GetActorLocation();

	FCollisionQueryParams Params(FName(TEXT("SkillRadius")),false,Character);
	GetWorld()->OverlapMultiByChannel(
	    Overlaps,
		Origin,
		FQuat::Identity,
		ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(SkillRadius),Params);

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

	FColor DrawColor = HitActors.Num() > 0 ? FColor::Green : FColor::Red;
	DrawDebugSphere(GetWorld(),Origin,SkillRadius,16,DrawColor,false,5.0f);

	return FGameplayAbilityTargetDataHandle(ActorsData);
}
