// Fill out your copyright notice in the Description page of Project Settings.


#include "Stat/UAttackRadiusStat.h"

UAttackRadiusStat::UAttackRadiusStat()
	:
	Super::UBaseStat(),
	AttackRadius(0.f)
{}

float UAttackRadiusStat::GetAttackRadius() const
{
	return AttackRadius;
}

void UAttackRadiusStat::SetAttackRadius(float radius)
{
	AttackRadius = radius;
}

