// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter/ABaseEnemyCharacter.h"
#include "AbilitySystem\Attributes\UHealthAttributeSet.h"
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
		UHealthAttributeSet* healthAttribute = CreateDefaultSubobject<UHealthAttributeSet>("Health Attribute Set");
		healthAttribute->InitHealth(30.f);
		healthAttribute->InitMaxHealth(50.f);
	}
}

void ABaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}
