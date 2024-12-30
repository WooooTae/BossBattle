// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidget.generated.h"

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API UTitleWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//UTitleWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnNewGamButtonClicked();

	UFUNCTION()
	void OnExitGameButtonClicked();

private:
	UPROPERTY(VisibleAnywhere,BluePrintReadOnly,Category=Button,Meta=(AllowPrivateAccess,BindWidget))
	TObjectPtr<class UButton> NewGameButton;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = Button, Meta = (AllowPrivateAccess, BindWidget))
	TObjectPtr<class UButton> ExitGameButton;
};
