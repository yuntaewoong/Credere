// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AWarriorCharacter.h"
#include "Navigation/UNavigationComponent.h"

AWarriorCharacter::AWarriorCharacter()
	: 
	Super::ABaseCharacter(),
	Navigation(nullptr),
	SkeletalMeshZAdjust(-80.0),
	SkeletalMeshPitchAdjust(-90.0)
{
	//Navigation Component 
	Navigation = CreateDefaultSubobject<UNavigationComponent>(TEXT("Navigation"));
	

	//SkeletalMesh로딩
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalMesh(TEXT("SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));
	if (skeletalMesh.Succeeded())
		GetMesh()->SetSkeletalMesh(skeletalMesh.Object);
	else
		UE_LOG(LogSkeletalMesh, Error, TEXT("Warrior Skeletal Mesh Not Loaded"));

	//Animation Blueprint로딩
	static const ConstructorHelpers::FObjectFinder<UAnimBlueprint> animationBlueprint(TEXT("AnimBlueprint'/Game/Blueprints/AnimationBlueprints/WarriorAnimationBP.WarriorAnimationBP'"));
	if (animationBlueprint.Succeeded())
		GetMesh()->SetAnimInstanceClass(animationBlueprint.Object->GeneratedClass);
	else
		UE_LOG(LogSkeletalMesh, Error, TEXT("Warrior AnimBP Not Loaded"));
	
	GetMesh()->AddRelativeLocation(FVector(0.0, 0.0, SkeletalMeshZAdjust));
	GetMesh()->AddRelativeRotation(FQuat(FRotator(0.0,SkeletalMeshPitchAdjust,0.0)));

	
}

void AWarriorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Navigation->SetEndPoint(FVector(10000.0,0.0,0.0));
}
