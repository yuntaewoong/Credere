// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter/ABaseEnemyCharacter.h"
#include "AbilitySystem\UCredereAbilitySystemComponent.h"

// Sets default values
ABaseEnemyCharacter::ABaseEnemyCharacter()
	:
	Super::ACharacter(),
	AbilitySystemComponent(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;
	{//Ability System설정
		AbilitySystemComponent = CreateDefaultSubobject<UCredereAbilitySystemComponent>(TEXT("Ability System"));
	}
}

void ABaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}
