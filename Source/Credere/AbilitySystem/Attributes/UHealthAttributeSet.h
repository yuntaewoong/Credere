// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
private:
	
	UPROPERTY(VisibleAnywhere, Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData Health;

	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;
};
