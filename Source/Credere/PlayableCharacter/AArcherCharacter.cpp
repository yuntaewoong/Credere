// Fill out your copyright notice in the Description page of Project Settings.


#include "AArcherCharacter.h"

AArcherCharacter::AArcherCharacter()
	:
	Super::ABasePlayableCharacter(),
	SkeletalMeshZAdjust(-80.0),
	SkeletalMeshYawAdjust(-90.0)
{
	{//SkeletalMesh로딩
		static const ConstructorHelpers::FObjectFinder<USkeletalMesh>
			skeletalMesh(TEXT("SkeletalMesh'/Game/ParagonSparrow/Characters/Heroes/Sparrow/Meshes/Sparrow.Sparrow'"));
		if (!skeletalMesh.Succeeded())
			UE_LOG(LogSkeletalMesh, Error, TEXT("Archer Skeletal Mesh Not Loaded"));
		GetMesh()->SetSkeletalMesh(skeletalMesh.Object);
	}	
	{//Animation Blueprint로딩
		static const ConstructorHelpers::FObjectFinder<UAnimBlueprint> 
			animationBlueprint(TEXT("AnimBlueprint'/Game/Blueprints/AnimationBlueprints/ArcherAnimBP.ArcherAnimBP'"));
		if (!animationBlueprint.Succeeded())
			UE_LOG(LogSkeletalMesh, Error, TEXT("Archer AnimBP Not Loaded"));
		GetMesh()->SetAnimInstanceClass(animationBlueprint.Object->GeneratedClass);
	}
	{//Attack1 Anim Montage로딩
		static const ConstructorHelpers::FObjectFinder<UAnimMontage> 
			attack1AnimMontage(TEXT("AnimMontage'/Game/ParagonSparrow/Characters/Heroes/Sparrow/Animations/Primary_Fire_Med_Montage.Primary_Fire_Med_Montage'"));
		if(!attack1AnimMontage.Succeeded())
			UE_LOG(LogActor,Error, TEXT("Warrior Attack1 Not Loaded"));
		SetAttack1AnimMontage(attack1AnimMontage.Object);
	}
	GetMesh()->AddRelativeLocation(FVector(0.0, 0.0, SkeletalMeshZAdjust));
	GetMesh()->AddRelativeRotation(FQuat(FRotator(0.0,SkeletalMeshYawAdjust,0.0)));
}

void AArcherCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AArcherCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}