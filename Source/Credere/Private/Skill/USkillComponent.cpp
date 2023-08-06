// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill\USkillComponent.h"
#include "Skill\UBaseSkill.h"
#include "Skill\UAutoAttackSkill.h"

USkillComponent::USkillComponent()
	:
	Super::UActorComponent(),
	Skills()
{
	PrimaryComponentTick.bCanEverTick = true;
	Skills[static_cast<uint8>(ESkillType::AUTO_ATTACK)] = NewObject<UAutoAttackSkill>();
}


void USkillComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void USkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USkillComponent::SetStatActive(ESkillType customSkillType, bool isActive)
{
	Skills[static_cast<uint8>(customSkillType)]->SetActive(isActive);
}

