// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter/ABattleMageCharacter.h"

ABattleMageCharacter::ABattleMageCharacter()
	:
	Super::ABasePlayableCharacter(),
	SkeletalMeshZAdjust(-80.0),
	SkeletalMeshYawAdjust(-90.0)
{
	{//SkeletalMesh로딩
		static const ConstructorHelpers::FObjectFinder<USkeletalMesh> 
			skeletalMesh(TEXT("SkeletalMesh'/Game/ParagonSerath/Characters/Heroes/Serath/Meshes/Serath.Serath'"));
		if (!skeletalMesh.Succeeded())
			UE_LOG(LogSkeletalMesh, Error, TEXT("BattleMage Skeletal Mesh Not Loaded"));
		GetMesh()->SetSkeletalMesh(skeletalMesh.Object);
	}	
	{//Animation Blueprint로딩
		static const ConstructorHelpers::FObjectFinder<UAnimBlueprint>
			animationBlueprint(TEXT("AnimBlueprint'/Game/Blueprints/AnimationBlueprints/BattleMageAnimBP.BattleMageAnimBP'"));
		if (!animationBlueprint.Succeeded())
			UE_LOG(LogSkeletalMesh, Error, TEXT("BattleMage AnimBP Not Loaded"));
		GetMesh()->SetAnimInstanceClass(animationBlueprint.Object->GeneratedClass);
	}
	{//Attack1 Montage로딩
		static const ConstructorHelpers::FObjectFinder<UAnimMontage> 
			attack1AnimMontage(TEXT("AnimMontage'/Game/ParagonSerath/Characters/Heroes/Serath/Animations/Primary_Attack_A_Medium_Montage.Primary_Attack_A_Medium_Montage'"));
		if(!attack1AnimMontage.Succeeded())
			UE_LOG(LogActor,Error, TEXT("Warrior Attack1 Not Loaded"));
		SetAttack1AnimMontage(attack1AnimMontage.Object);
	}
	GetMesh()->AddRelativeLocation(FVector(0.0, 0.0, SkeletalMeshZAdjust));
	GetMesh()->AddRelativeRotation(FQuat(FRotator(0.0,SkeletalMeshYawAdjust,0.0)));
}

void ABattleMageCharacter::BeginPlay()
{	
	Super::BeginPlay();
}

void ABattleMageCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
