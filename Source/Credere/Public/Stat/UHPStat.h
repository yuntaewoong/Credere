// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Stat/UBaseStat.h"
#include "UHPStat.generated.h"

/**
 * 
 */
UCLASS()
class CREDERE_API UHPStat : public UBaseStat
{
	GENERATED_BODY()
public:
	UHPStat();
	void AddHP(uint16 hp);
	void SubtractHP(uint16 hp);
	uint16 GetHP() const;
private:
	static const uint16 MINIMUM_HP = 0u;
	uint16 Hp;
	uint16 MaxHp;

};
