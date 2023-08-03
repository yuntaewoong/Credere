// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayableCharacter/ABasePlayableCharacter.h"
#include "AWarriorCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CREDERE_API AWarriorCharacter : public ABasePlayableCharacter
{
	GENERATED_BODY()
public:
	AWarriorCharacter();
	virtual void Tick(float DeltaTime) override;
	
private:
	double SkeletalMeshZAdjust;
	double SkeletalMeshYawAdjust;
	
};
