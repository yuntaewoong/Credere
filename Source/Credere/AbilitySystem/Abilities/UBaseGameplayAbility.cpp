// Fill out your copyright notice in the Description page of Project Settings.


#include "UBaseGameplayAbility.h"

UBaseGameplayAbility::UBaseGameplayAbility()
    :
    Super::UGameplayAbility()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

