// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter/ABaseEnemyCharacter.h"
#include "Skill\ASkillHolder.h"
#include "Stat\AStatHolder.h"

// Sets default values
ABaseEnemyCharacter::ABaseEnemyCharacter()
	:
	Super::ACharacter(),
	StatHolder(nullptr),
	SkillHolder(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	{//StatHolder스폰
		StatHolder = GetWorld()->SpawnActor<AStatHolder>(
			FVector::ZeroVector,
			FRotator::ZeroRotator
		);
		StatHolder->AttachToActor(this,FAttachmentTransformRules::KeepRelativeTransform);
	}
	{//SKillHolder스폰
		SkillHolder = GetWorld()->SpawnActor<ASkillHolder>(
			FVector::ZeroVector,
			FRotator::ZeroRotator
		);
		SkillHolder->AttachToActor(this,FAttachmentTransformRules::KeepRelativeTransform);
		//SkillHolder->SetSkillActive(ESkillType::AUTO_ATTACK,true);
		SkillHolder->SetStatHolder(StatHolder);//스킬홀더가 사용할 스탯홀더에 대한 포인터 전달
	}
}
