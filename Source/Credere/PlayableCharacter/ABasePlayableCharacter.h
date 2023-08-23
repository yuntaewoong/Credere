// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "GameplayAbilitySpec.h"
#include "ABasePlayableCharacter.generated.h"

UCLASS(Abstract)
class CREDERE_API ABasePlayableCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABasePlayableCharacter();

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	TObjectPtr<class UAnimMontage> GetAttack1AnimMontage() const;
protected:
	void SetAttack1AnimMontage(TObjectPtr<class UAnimMontage> AnimMontage);
private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void AbilityJump();
	void StopAbilityJumping();
private:
	UPROPERTY()
	TObjectPtr<class ANavigation> Navigation;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UCredereAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UCameraComponent> FollowCamera;

	UPROPERTY()
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY()
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY()
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY()
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY()
	TObjectPtr<class UAnimMontage> Attack1AnimMontage;
	
	FGameplayAbilitySpecHandle JumpAbilitySpecHandle;
	FGameplayAbilitySpecHandle AutoAttackAbilitySpecHandle;


};
