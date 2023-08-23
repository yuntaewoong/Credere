// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/UBaseAttributeSet.h"
#include "UHealthAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class CREDERE_API UHealthAttributeSet : public UBaseAttributeSet
{
	GENERATED_BODY()
public:
	UHealthAttributeSet();

	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, MaxHealth);
private:
	
	UPROPERTY()
	FGameplayAttributeData Health;

	UPROPERTY()
	FGameplayAttributeData MaxHealth;
};
