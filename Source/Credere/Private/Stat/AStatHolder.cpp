// Fill out your copyright notice in the Description page of Project Settings.


#include "Stat\AStatHolder.h"
#include "Stat\UBaseStat.h"
#include "Stat\UHPStat.h"


AStatHolder::AStatHolder()
	:
	Super::AActor(),
	emptyComponent(nullptr),
	Stats()
{
	Stats[static_cast<uint8>(ECustomStatType::HP)] = NewObject<UHPStat>();
	emptyComponent = CreateDefaultSubobject<USceneComponent>(TEXT("EmptySceneComponent"));
	SetRootComponent(emptyComponent);
}
void AStatHolder::BeginPlay()
{
	Super::BeginPlay();
}

void AStatHolder::SetStatActive(ECustomStatType customStatType, bool isActive)
{
	Stats[static_cast<uint8>(customStatType)]->SetActive(isActive);
}

