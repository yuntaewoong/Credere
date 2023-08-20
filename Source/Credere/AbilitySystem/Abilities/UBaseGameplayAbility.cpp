// Fill out your copyright notice in the Description page of Project Settings.


#include "UBaseGameplayAbility.h"

DEFINE_LOG_CATEGORY(LogGameplayAbility);

UBaseGameplayAbility::UBaseGameplayAbility()
    :
    Super::UGameplayAbility()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

