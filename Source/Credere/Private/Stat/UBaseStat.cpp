// Fill out your copyright notice in the Description page of Project Settings.


#include "Stat/UBaseStat.h"

DEFINE_LOG_CATEGORY(LogCustomStat);

UBaseStat::UBaseStat()
	:
	Super::UObject(),
	bIsActive(false)
{
}

void UBaseStat::SetActive(bool isActive)
{
	bIsActive = isActive;
}
