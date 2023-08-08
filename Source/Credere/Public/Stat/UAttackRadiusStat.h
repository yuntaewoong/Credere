// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Stat/UBaseStat.h"
#include "UAttackRadiusStat.generated.h"

/**
 * 
 */
UCLASS()
class CREDERE_API UAttackRadiusStat : public UBaseStat
{
	GENERATED_BODY()
public:
	UAttackRadiusStat();
	float GetAttackRadius() const;
	void SetAttackRadius(float radius);
private:
	float AttackRadius;
};
