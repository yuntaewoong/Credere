// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AHumanPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CREDERE_API AHumanPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AHumanPlayerController();
	
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;
private:
	void ChangeCharacterForward();
	void ChangeCharacterBackward();

private:
	UPROPERTY()
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY()
	TObjectPtr<class UInputAction> CharacterForwardChangeAction;

	UPROPERTY()
	TObjectPtr<class UInputAction> CharacterBackwardChangeAction;
};
