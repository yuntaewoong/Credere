// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill\ASkillHolder.h"
#include "Skill\UAutoAttackSkill.h"
#include "Stat\AStatHolder.h"
#include "Stat\UAttackRadiusStat.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"

ASkillHolder::ASkillHolder()
	:
	Super::AActor(),
	SphereComponent(nullptr),
	Skills()
{
	PrimaryActorTick.bCanEverTick = true;//Tick On
	Skills[static_cast<uint8>(ESkillType::AUTO_ATTACK)] = CreateDefaultSubobject<UAutoAttackSkill>(TEXT("AutoAttack"));
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SetRootComponent(SphereComponent);
}


void ASkillHolder::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->bHiddenInGame = false;
	SphereComponent->SetVisibility(true);



	for(auto skill : Skills)
	{
		skill->BeginPlay();
	}
}

void ASkillHolder::Tick(float DeltaTime)
{
	if(!StatHolder)
		return;
	float attackRadius = StatHolder->GetAttackRadiusStat()->GetAttackRadius();
	SphereComponent->SetSphereRadius(attackRadius);
}

void ASkillHolder::SetSkillActive(ESkillType customSkillType, bool isActive)
{
	Skills[static_cast<uint8>(customSkillType)]->SetActive(isActive);
}

void ASkillHolder::SetStatHolder(const AStatHolder* statHolder)
{
	StatHolder = statHolder;
}

