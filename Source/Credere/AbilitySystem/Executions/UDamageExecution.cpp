// Fill out your copyright notice in the Description page of Project Settings.


#include "UDamageExecution.h"
#include "AbilitySystem\Attributes\UHealthAttributeSet.h"
DEFINE_LOG_CATEGORY(LogExecution);

UDamageExecution::UDamageExecution()
	:
	Super::UGameplayEffectExecutionCalculation()
{
}

void UDamageExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UE_LOG(LogExecution,Warning,TEXT("Execute Called"));
}
