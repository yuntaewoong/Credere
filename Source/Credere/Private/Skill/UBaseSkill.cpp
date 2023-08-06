// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/UBaseSkill.h"
DEFINE_LOG_CATEGORY(LogSkill);

UBaseSkill::UBaseSkill()
	:
	Super::UObject()
{}

void UBaseSkill::SetActive(bool isActive)
{
	bIsActive = isActive;
}

bool UBaseSkill::IsActive() const
{
	return bIsActive;
}
