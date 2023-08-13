// Fill out your copyright notice in the Description page of Project Settings.

#include "Skill\ASkillHolder.h"
#include "PlayableCharacter\ABasePlayableCharacter.h"
#include "EnemyCharacter\ABaseEnemyCharacter.h"
#include "Skill\UAutoAttackSkill.h"
#include "Stat\AStatHolder.h"
#include "Stat\UAttackRadiusStat.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"

ASkillHolder::ASkillHolder()
	:
	Super::AActor(),
	SphereComponent(nullptr),
	AutoAttackSkill(nullptr),
	TargetingActor(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;//Tick On
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SetRootComponent(SphereComponent);
	SphereComponent->SetGenerateOverlapEvents(true);

	AutoAttackSkill = CreateDefaultSubobject<UAutoAttackSkill>(TEXT("AutoAttack"));
}


void ASkillHolder::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->bHiddenInGame = false;
	SphereComponent->SetVisibility(true);
}

void ASkillHolder::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	AActor* parentActor = nullptr;
	parentActor = GetAttachParentActor();
	if(!parentActor)
	{
		UE_LOG(LogSkill,Warning,TEXT("SkillHolder is not Set to Character Actor"));
		return;
	}
	if(
		parentActor->GetClass()->IsChildOf(ABasePlayableCharacter::StaticClass()) &&
		OtherActor->GetClass()->IsChildOf(ABaseEnemyCharacter::StaticClass()) ||
		OtherActor->GetClass()->IsChildOf(ABasePlayableCharacter::StaticClass()) &&
		parentActor->GetClass()->IsChildOf(ABaseEnemyCharacter::StaticClass())
	)
	{
	//case1. 부모가 Playable이고 OtherActor가 Enemy일 때
	//case2. 부모가 Enemy이고 OtherActor가 Playable일 때
		TargetingActor = OtherActor;
		UE_LOG(LogSkill,Warning,TEXT("Opponent Detected"));
	}
}

void ASkillHolder::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	if(TargetingActor != nullptr && TargetingActor == OtherActor)
	{
		TargetingActor = nullptr;
		UE_LOG(LogSkill,Warning,TEXT("Opponent OverlapEnd"));
	}
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

