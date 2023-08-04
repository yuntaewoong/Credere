// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter/AWarriorCharacter.h"

AWarriorCharacter::AWarriorCharacter()
	: 
	Super::ABasePlayableCharacter(),
	SkeletalMeshZAdjust(-80.0),
	SkeletalMeshYawAdjust(-90.0)
{
	//SkeletalMesh로딩
	static const ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalMesh(TEXT("SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));
	if (!skeletalMesh.Succeeded())
		UE_LOG(LogSkeletalMesh, Error, TEXT("Warrior Skeletal Mesh Not Loaded"));
	GetMesh()->SetSkeletalMesh(skeletalMesh.Object);
		
	//Animation Blueprint로딩
	static const ConstructorHelpers::FObjectFinder<UAnimBlueprint> animationBlueprint(TEXT("AnimBlueprint'/Game/Blueprints/AnimationBlueprints/WarriorAnimBP.WarriorAnimBP'"));
	if (!animationBlueprint.Succeeded())
		UE_LOG(LogSkeletalMesh, Error, TEXT("Warrior AnimBP Not Loaded"));
	GetMesh()->SetAnimInstanceClass(animationBlueprint.Object->GeneratedClass);

	GetMesh()->AddRelativeLocation(FVector(0.0, 0.0, SkeletalMeshZAdjust));
	GetMesh()->AddRelativeRotation(FQuat(FRotator(0.0,SkeletalMeshYawAdjust,0.0)));
}

void AWarriorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
