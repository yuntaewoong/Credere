// Fill out your copyright notice in the Description page of Project Settings.


#include "UCredereGameplayAbility_Jump.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UCredereGameplayAbility_Jump::UCredereGameplayAbility_Jump()
	:
	Super::UCredereGameplayAbility()
{}

bool UCredereGameplayAbility_Jump::CanActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo * ActorInfo,
	const FGameplayTagContainer * SourceTags,
	const FGameplayTagContainer * TargetTags,
	OUT FGameplayTagContainer * OptionalRelevantTags
) const
{
	ACharacter* character = nullptr;
	UCharacterMovementComponent* characterMovement = nullptr;
	if(ActorInfo->OwnerActor != nullptr)
	{
		character =  Cast<ACharacter>(ActorInfo->OwnerActor);
		if(!character)
			return false;
		characterMovement = character->GetCharacterMovement();
		if(!characterMovement)
			return false;
	}
	
	return !characterMovement->IsFalling();
}

void UCredereGameplayAbility_Jump::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData
)
{
	if(ActorInfo->OwnerActor != nullptr)
	{
		ACharacter* character =  Cast<ACharacter>(ActorInfo->OwnerActor);
		if(character)
		{
			character->Jump();
		}
	}
	Super::ActivateAbility(Handle,ActorInfo,ActivationInfo,TriggerEventData);
}

void UCredereGameplayAbility_Jump::EndAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility,
	bool bWasCancelled
)
{
	Super::EndAbility(Handle,ActorInfo,ActivationInfo,bReplicateEndAbility,bWasCancelled);
}
