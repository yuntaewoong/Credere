// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ABaseCharacter.h"
#include "ASummonerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CREDERE_API ASummonerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	ASummonerCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
private:
	double SkeletalMeshZAdjust;
	double SkeletalMeshYawAdjust;
};
