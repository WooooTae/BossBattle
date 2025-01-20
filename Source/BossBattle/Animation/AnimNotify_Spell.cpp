// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_Spell.h"
#include "BossBattle/Prop/Fireball.h"
#include "Kismet/GameplayStatics.h"

void UAnimNotify_Spell::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    FName SocketName = TEXT("SpellSocket");

    if (MeshComp->DoesSocketExist(SocketName))
    {
        AActor* Character = MeshComp->GetOwner();
        if (Character && FireballClass)
        {
            AFireball* fireball = Character->GetWorld()->SpawnActor<AFireball>(FireballClass, MeshComp->GetSocketLocation(SocketName), Character->GetActorRotation());
        }
    }
}
