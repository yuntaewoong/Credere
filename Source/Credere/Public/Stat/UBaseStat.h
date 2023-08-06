// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UBaseStat.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCustomStat, Log, All);
/**
 * 
 */
UCLASS(Abstract)
class CREDERE_API UBaseStat : public UObject
{
	GENERATED_BODY()
public:
	UBaseStat();
	void SetActive(bool isActive);
private:
	bool bIsActive;
};
