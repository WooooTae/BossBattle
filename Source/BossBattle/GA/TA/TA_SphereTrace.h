// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TA_Trace.h"
#include "TA_SphereTrace.generated.h"

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API ATA_SphereTrace : public ATA_Trace
{
	GENERATED_BODY()
	
protected:
	virtual FGameplayAbilityTargetDataHandle MakeTargetData() const override;
};
