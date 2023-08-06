// Fill out your copyright notice in the Description page of Project Settings.


#include "Stat\UStatComponent.h"
#include "Stat\UBaseStat.h"
#include "Stat\UHPStat.h"


UStatComponent::UStatComponent()
	:
	Super::UActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	Stats[static_cast<uint8>(ECustomStatType::HP)] = NewObject<UHPStat>();
}
void UStatComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UStatComponent::SetStatActive(ECustomStatType customStatType, bool isActive)
{
	Stats[static_cast<uint8>(customStatType)]->SetActive(isActive);
}

