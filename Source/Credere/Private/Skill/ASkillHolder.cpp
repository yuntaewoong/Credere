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
	AutoAttackSkill(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;//Tick On
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SetRootComponent(SphereComponent);

	AutoAttackSkill = CreateDefaultSubobject<UAutoAttackSkill>(TEXT("AutoAttack"));
}


void ASkillHolder::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->bHiddenInGame = false;
	SphereComponent->SetVisibility(true);
}

void ASkillHolder::Tick(float DeltaTime)
{
	if(!StatHolder)
		return;
	float attackRadius = StatHolder->GetAttackRadiusStat()->GetAttackRadius();
	SphereComponent->SetSphereRadius(attackRadius);
}


void ASkillHolder::SetStatHolder(const AStatHolder* statHolder)
{
	StatHolder = statHolder;
}

