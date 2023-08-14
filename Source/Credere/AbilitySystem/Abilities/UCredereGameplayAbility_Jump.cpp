// Fill out your copyright notice in the Description page of Project Settings.


#include "UCredereGameplayAbility_Jump.h"

UCredereGameplayAbility_Jump::UCredereGameplayAbility_Jump()
	:
	Super::UCredereGameplayAbility()
{}

bool UCredereGameplayAbility_Jump::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayTagContainer * SourceTags, const FGameplayTagContainer * TargetTags, OUT FGameplayTagContainer * OptionalRelevantTags) const
{
	return false;
}

void UCredereGameplayAbility_Jump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
}

void UCredereGameplayAbility_Jump::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
}
