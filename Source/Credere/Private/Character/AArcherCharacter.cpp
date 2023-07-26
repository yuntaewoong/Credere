// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AArcherCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AArcherCharacter::AArcherCharacter()
	:
	Super::ABaseCharacter()
{
	//SkeletalMesh로딩
	static const ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalMesh(TEXT("SkeletalMesh'/Game/ParagonSparrow/Characters/Heroes/Sparrow/Meshes/Sparrow.Sparrow'"));
	if (!skeletalMesh.Succeeded())
		UE_LOG(LogSkeletalMesh, Error, TEXT("Archer Skeletal Mesh Not Loaded"));
	GetMesh()->SetSkeletalMesh(skeletalMesh.Object);

}

void AArcherCharacter::BeginPlay()
{
	SpawnDefaultController();
	Super::BeginPlay();
	
}

void AArcherCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}