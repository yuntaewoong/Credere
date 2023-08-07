// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/UAutoAttackSkill.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"

UAutoAttackSkill::UAutoAttackSkill()
	:
	Super::UBaseSkill()
{
}

void UAutoAttackSkill::Tick(float Deltatime)
{
	
}

void UAutoAttackSkill::BeginPlay()
{
	//SphereComponent->SetupAttachment(OwnerCharacter->GetRootComponent());
}
