// Fill out your copyright notice in the Description page of Project Settings.


#include "Stat/UHPStat.h"

UHPStat::UHPStat()
	:
	Super::UBaseStat(),
	Hp(0u),
	MaxHp(100u)
{
}

void UHPStat::AddHP(uint16 hp)
{
	if(!bIsActive)
	{
		UE_LOG(LogCustomStat,Warning,TEXT("Stat is not Active"));
		return;
	}
	if(Hp + hp > MaxHp)
	{
		UE_LOG(LogCustomStat,Warning,TEXT("Exceed Max Hp Value"));
		return;
	}
	Hp += hp;
}

void UHPStat::SubtractHP(uint16 hp)
{
	if(!bIsActive)
	{
		UE_LOG(LogCustomStat,Warning,TEXT("Stat is not Active"));
		return;
	}
	if (Hp - hp < MINIMUM_HP)
	{
		UE_LOG(LogCustomStat,Warning,TEXT("Cannot Set HP under MINIMUM_HP"));
		return;
	}
	Hp -= hp;
}

uint16 UHPStat::GetHP() const
{
	return Hp;
}
