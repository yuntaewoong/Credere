// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
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
	
private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
private:
	UPROPERTY(VisibleAnywhere)
	class UNavigationComponent* NavigationComponent;

	UPROPERTY()
	class AStatHolder* StatHolder;

	UPROPERTY()
	class ASkillHolder* SkillHolder;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* FollowCamera;

	UPROPERTY()
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY()
	class UInputAction* JumpAction;

	UPROPERTY()
	class UInputAction* MoveAction;

	UPROPERTY()
	class UInputAction* LookAction;
};
