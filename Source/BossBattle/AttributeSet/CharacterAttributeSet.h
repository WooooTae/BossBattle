// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CharacterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API UCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UCharacterAttributeSet();

	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, AttackRange);
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MaxAttackRange);
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, AttackRadius);
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MaxAttackRadius);
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, AttackRate);
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MaxAttackRate);
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Damage);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOutOfHealthDelegate);

	mutable FOutOfHealthDelegate OnOutOfHealth;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRange;

	UPROPERTY(BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackRange;

	UPROPERTY(BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRadius;

	UPROPERTY(BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackRadius;

	UPROPERTY(BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRate;

	UPROPERTY(BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackRate;

	UPROPERTY(BlueprintReadOnly, Category = Health, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, Category = Health, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Damage;

	bool bOutOfHealth = false;

	friend class UGE_AttackDamage;
};
