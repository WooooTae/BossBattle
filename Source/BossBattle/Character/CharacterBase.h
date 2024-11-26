// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CharacterBase.generated.h"

UCLASS()
class BOSSBATTLE_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACharacterBase();

public:
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	FORCEINLINE class UAnimMontage* GetComboActionMontage() const { return ComboActionMontage; }
	FORCEINLINE class UComboActionData* GetComboActionData() const { return ComboActionData; }

protected:
	virtual void SetDead();
	void PlayDeadAnimation();

	float DeadEventDelayTime = 5.0f;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Stat,Meta=(PrivateAccess=true))
	TObjectPtr<class UAnimMontage> DeadMontage;

protected:
	UPROPERTY(VisibleAnywhere,BluePrintReadOnly,Category=Equiqment,Meta=(AllowPrivateAccess))
	TObjectPtr<class USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY(EditAnywhere, Category = GAS)
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;

	UPROPERTY(EditAnywhere, Category = GAS)
	TMap<int32, TSubclassOf<class UGameplayAbility>> StartInputAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> ComboActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UComboActionData> ComboActionData;
};
