// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter/ABaseEnemyCharacter.h"
#include "ADualBladeEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CREDERE_API ADualBladeEnemyCharacter : public ABaseEnemyCharacter
{
	GENERATED_BODY()
public:
	ADualBladeEnemyCharacter();
protected:
	virtual void Tick(float DeltaTime) override;
private:
	double SkeletalMeshZAdjust;
	double SkeletalMeshYawAdjust;
};
