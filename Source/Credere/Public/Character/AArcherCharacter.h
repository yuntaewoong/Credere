// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ABaseCharacter.h"
#include "AArcherCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CREDERE_API AArcherCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	AArcherCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
private:
	double SkeletalMeshZAdjust;
	double SkeletalMeshYawAdjust;
};
