// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter/ABaseEnemyCharacter.h"

// Sets default values
ABaseEnemyCharacter::ABaseEnemyCharacter()
	:
	Super::ACharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}
