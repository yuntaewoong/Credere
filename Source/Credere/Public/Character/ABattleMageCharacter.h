// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ABaseCharacter.h"
#include "ABattleMageCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CREDERE_API ABattleMageCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	ABattleMageCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(VisibleAnywhere)
	class UNavigationComponent* Navigation;

	double SkeletalMeshZAdjust;
	double SkeletalMeshYawAdjust;
};
