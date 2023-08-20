// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities\GameplayAbility.h"
#include "UBaseGameplayAbility.generated.h"
DECLARE_LOG_CATEGORY_EXTERN(LogGameplayAbility, Log, All);
/**
 * 
 */
UCLASS(Abstract)
class CREDERE_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UBaseGameplayAbility();

};
