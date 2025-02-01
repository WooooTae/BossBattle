// Fill out your copyright notice in the Description page of Project Settings.

#include "Fireball.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "BossBattle/AttributeSet/CharacterAttributeSet.h"
#include "Abilities/GameplayAbility.h"
#include "Kismet/GameplayStatics.h"
#include "BossBattle/Character/NonCharacterPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AFireball::AFireball()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    CollisionComponent->InitSphereRadius(300.0f);
    CollisionComponent->SetCollisionProfileName(TEXT("Projectile"));
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
    CollisionComponent->SetCollisionResponseToChannel(ECC_EngineTraceChannel3, ECollisionResponse::ECR_Overlap); // 또는 적절한 채널
    RootComponent = CollisionComponent;

    FireballEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireballEffect"));
    FireballEffect->SetupAttachment(RootComponent);

    static const ConstructorHelpers::FClassFinder<UGameplayEffect> FireballCalssRef(TEXT("/Game/BossBattle/Blueprint/GE/BPGE_FireballDamage.BPGE_FireballDamage_C"));
    if (FireballCalssRef.Class)
    {
        AttackDamageEffect = FireballCalssRef.Class;
    }
    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this,&AFireball::OnOverlap);
    CollisionComponent->OnComponentEndOverlap.AddDynamic(this,&AFireball::OnEndOverlap);
}

// Called when the game starts or when spawned
void AFireball::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AFireball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    FVector Forward = GetActorForwardVector();
    SetActorLocation(GetActorLocation() + Forward * Speed * DeltaTime);
}

void AFireball::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{ 
    UE_LOG(LogTemp,Log,TEXT("Overlap On"));

    ANonCharacterPlayer* Character = Cast<ANonCharacterPlayer>(OtherActor);

    if (nullptr != Character)
    {
        Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
        UE_LOG(LogTemp, Log, TEXT("Casting On"));
        UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
        AnimInstance->Montage_Play(Character->GetHittedMontage(), 1.0f);

        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, OtherActor->GetActorLocation(), OtherActor->GetActorRotation());
    }

    if (OtherActor && OtherActor == Character)
    {
        UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
        if (TargetASC && AttackDamageEffect)
        {
            FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(AttackDamageEffect, 1.0f, TargetASC->MakeEffectContext());
            if (EffectSpecHandle.IsValid())
            {
                TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
            }
        }
        FireballEffect->Deactivate();
        Destroy();
    }
}

void AFireball::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    ANonCharacterPlayer* Character = Cast<ANonCharacterPlayer>(OtherActor);

    if (nullptr != Character)
    {
        Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking); 
    }
}

