// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BossBattle/Interface/NPCAIInterface.h"
#include "CharacterBase.generated.h"

UCLASS()
class BOSSBATTLE_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACharacterBase();

public:
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	FORCEINLINE bool GetDeadCondition() const { return IsDead; }
	FORCEINLINE class UAnimMontage* GetHittedMontage() const { return HittedMontage; }
	FORCEINLINE class UAnimMontage* GetComboActionMontage() const { return ComboActionMontage; }
	FORCEINLINE class UAnimMontage* GetBasicSkillMontage() const { return BasicSkillMontage; }
	FORCEINLINE class UComboActionData* GetComboActionData() const { return ComboActionData; }

	FAICharacterAttackFinished OnAttackFinished;

	void NotifyComboActionEnd();

	UPROPERTY()
	bool IsDead;

protected:
	virtual void SetDead();

	float DeadEventDelayTime = 3.0f;

protected:
	UPROPERTY(VisibleAnywhere,BluePrintReadOnly,Category=Equiqment,Meta=(AllowPrivateAccess))
	TObjectPtr<class USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GAS)
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;

	UPROPERTY(EditAnywhere, Category = GAS)
	TMap<int32, TSubclassOf<class UGameplayAbility>> StartInputAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> HittedMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> ComboActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UComboActionData> ComboActionData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> BasicSkillMontage;
};
