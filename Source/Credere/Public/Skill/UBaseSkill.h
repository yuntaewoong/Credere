// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UBaseSkill.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSkill, Log, All);
/**
 * 
 */
UCLASS(Abstract)
class CREDERE_API UBaseSkill : public UObject
{
	GENERATED_BODY()
public:
	UBaseSkill();
	virtual void Tick(float DeltaTime) PURE_VIRTUAL(UBaseSkill::Tick,);
	virtual void BeginPlay() PURE_VIRTUAL(UBaseSkill::BeginPlay,);
	void SetActive(bool isActive);
	bool IsActive() const;
protected:
	bool bIsActive;
};
