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
	void Attack(class AActor* attacker, class AActor* attackTarget);
private:
	
};
