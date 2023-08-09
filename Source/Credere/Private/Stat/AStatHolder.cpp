// Fill out your copyright notice in the Description page of Project Settings.


#include "Stat\AStatHolder.h"
#include "Stat\UBaseStat.h"
#include "Stat\UHPStat.h"
#include "Stat\UAttackRadiusStat.h"


AStatHolder::AStatHolder()
	:
	Super::AActor(),
	EmptyComponent(nullptr),
	HpStat(nullptr),
	AttackRadiusStat(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;//Tick On
	EmptyComponent = CreateDefaultSubobject<USceneComponent>(TEXT("EmptySceneComponent"));
	HpStat = CreateDefaultSubobject<UHPStat>(TEXT("HP Stat"));
	AttackRadiusStat = CreateDefaultSubobject<UAttackRadiusStat>(TEXT("Attack Stat"));
	SetRootComponent(EmptyComponent);
}
void AStatHolder::BeginPlay()
{
	Super::BeginPlay();
}


UHPStat* AStatHolder::GetHpStat() const
{
	return HpStat;
}

UAttackRadiusStat* AStatHolder::GetAttackRadiusStat() const
{
	return AttackRadiusStat;
}
