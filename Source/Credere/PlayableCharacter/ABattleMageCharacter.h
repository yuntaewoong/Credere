// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayableCharacter/ABasePlayableCharacter.h"
#include "ABattleMageCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CREDERE_API ABattleMageCharacter : public ABasePlayableCharacter
{
	GENERATED_BODY()
public:
	ABattleMageCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
private:
	double SkeletalMeshZAdjust;
	double SkeletalMeshYawAdjust;
};
