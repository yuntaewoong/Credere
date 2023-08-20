// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/UBaseGameplayAbility.h"
#include "UGameplayAbility_AutoAttack.generated.h"

/**
 * 
 */
UCLASS()
class CREDERE_API UGameplayAbility_AutoAttack : public UBaseGameplayAbility
{
	GENERATED_BODY()
public:
	UGameplayAbility_AutoAttack();

	virtual bool CanActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayTagContainer* SourceTags = nullptr,
		const FGameplayTagContainer* TargetTags = nullptr,
		OUT FGameplayTagContainer* OptionalRelevantTags = nullptr
	) const override;

	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData
	) override;

	virtual void EndAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility, 
		bool bWasCancelled
	) override;
private:
	UFUNCTION()
	void AttackRepeat(int32 ActionNumber);

	void Attack();
private:
	FGameplayAbilitySpecHandle AbilitySpecHandle;
	const FGameplayAbilityActorInfo* AbilityActorInfo;
	FGameplayAbilityActivationInfo AbilityActivationInfo;
	TSubclassOf<UGameplayEffect> GE_DamageBPClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class ATriggerDetector> TriggerDetector;

	TObjectPtr<class UAbilityTask_Repeat> RepeatAbilityTask;
	float AutoAttackInterval;
	FDateTime LastAttackTime;
};
