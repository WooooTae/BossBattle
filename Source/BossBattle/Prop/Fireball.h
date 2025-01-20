// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Fireball.generated.h"

UCLASS()
class BOSSBATTLE_API AFireball : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireball();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, Category = Movement)
	float Speed = 1200.0f; 

	UPROPERTY(EditAnywhere, Category = Component)
	class USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, Category = Component)
	class UParticleSystemComponent* FireballEffect;

	UPROPERTY(EditAnywhere, Category = GAS)
	TSubclassOf<class UGameplayEffect> AttackDamageEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayCue)
	class UParticleSystem* ParticleSystem;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
