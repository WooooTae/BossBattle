// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ComboActionData.generated.h"

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API UComboActionData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UComboActionData();

	UPROPERTY(EditAnywhere,Category=Name)
	FString MontageSectionNamePrefix;

	UPROPERTY(EditAnywhere,Category=Data)
	uint8 MaxComboCount;

	UPROPERTY(EditAnywhere,Category=Data)
	float FrameRate;

	UPROPERTY(EditAnywhere,Category=Data)
	TArray<float> EffectiveFrameCount;
};
