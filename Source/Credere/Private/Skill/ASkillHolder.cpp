// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill\ASkillHolder.h"
#include "Skill\UBaseSkill.h"
#include "Skill\UAutoAttackSkill.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"

ASkillHolder::ASkillHolder()
	:
	Super::AActor(),
	SphereComponent(nullptr),
	Skills()
{
	Skills[static_cast<uint8>(ESkillType::AUTO_ATTACK)] = NewObject<UAutoAttackSkill>();
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SetRootComponent(SphereComponent);
}


void ASkillHolder::BeginPlay()
{
	Super::BeginPlay();
	for(auto skill : Skills)
	{
		skill->BeginPlay();
	}
}

void ASkillHolder::SetSkillActive(ESkillType customSkillType, bool isActive)
{
	Skills[static_cast<uint8>(customSkillType)]->SetActive(isActive);
}

