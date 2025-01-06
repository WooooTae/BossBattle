// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "NPCSkillAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API UNPCSkillAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UNPCSkillAttributeSet();

	ATTRIBUTE_ACCESSORS(UNPCSkillAttributeSet, SkillRange);
	ATTRIBUTE_ACCESSORS(UNPCSkillAttributeSet, MaxSkillRange);
	ATTRIBUTE_ACCESSORS(UNPCSkillAttributeSet, SkillAttackRate);
	ATTRIBUTE_ACCESSORS(UNPCSkillAttributeSet, MaxSkillAttackRate);
	ATTRIBUTE_ACCESSORS(UNPCSkillAttributeSet, SkillEnergy);
	ATTRIBUTE_ACCESSORS(UNPCSkillAttributeSet, MaxSkillEnergy);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData SkillRange;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxSkillRange;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData SkillAttackRate;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxSkillAttackRate;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData SkillEnergy;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxSkillEnergy;
};
