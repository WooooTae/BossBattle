// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "InputActionValue.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API APlayerCharacter : public ACharacterBase,public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void SetupGASInputComponent();
	void GASInputPressed(int32 InputId);
	void GASInputReleased(int32 InputId);

protected:
	UPROPERTY(EditAnywhere,Category=GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY(EditAnywhere,Category=GAS)
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;

	UPROPERTY(EditAnywhere,Category=GAS)
	TMap<int32, TSubclassOf<class UGameplayAbility>> StartInputAbilities;

	//Camera
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Camera,Meta=(AllowPrivateAccess=true))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = true))
	TObjectPtr<class UCameraComponent> FollowCamera;

	//Input
protected:
	UPROPERTY(EditAnywhere,BluePrintReadOnly,Category=Input,Meta=(AllowPrivateAccess="true"))
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BluePrintReadOnly,Category=Input,Meta=(AllowPrivateAccess="true"))
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BluePrintReadOnly,Category=Input,Meta=(AllowPrivateAccess="true"))
	TObjectPtr<class UInputAction> JumpAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere,Category=Weapon)
	TObjectPtr<class USkeletalMesh> WeaponMesh;
};
