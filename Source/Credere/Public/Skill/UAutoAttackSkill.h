// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/UBaseSkill.h"
#include "UAutoAttackSkill.generated.h"

/**
 * 
 */
UCLASS()
class CREDERE_API UAutoAttackSkill : public UBaseSkill
{
	GENERATED_BODY()
public:
	UAutoAttackSkill();
	virtual void Tick(float Deltatime) override;
	virtual void BeginPlay() override;
private:
};
