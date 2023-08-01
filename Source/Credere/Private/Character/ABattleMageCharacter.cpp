// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABattleMageCharacter.h"
#include "Navigation\UNavigationComponent.h"

ABattleMageCharacter::ABattleMageCharacter()
	:
	Super::ABaseCharacter(),
	Navigation(nullptr),
	SkeletalMeshZAdjust(-80.0),
	SkeletalMeshYawAdjust(-90.0)
{

	//Navigation Component	부착
	Navigation = CreateDefaultSubobject<UNavigationComponent>(TEXT("Navigation"));
	Navigation->SetupAttachment(RootComponent);

	//SkeletalMesh로딩
	static const ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalMesh(TEXT("SkeletalMesh'/Game/ParagonSerath/Characters/Heroes/Serath/Meshes/Serath.Serath'"));
	if (!skeletalMesh.Succeeded())
		UE_LOG(LogSkeletalMesh, Error, TEXT("Summoner Skeletal Mesh Not Loaded"));
	GetMesh()->SetSkeletalMesh(skeletalMesh.Object);
		
	//Animation Blueprint로딩
	static const ConstructorHelpers::FObjectFinder<UAnimBlueprint> animationBlueprint(TEXT("AnimBlueprint'/Game/Blueprints/AnimationBlueprints/BattleMageAnimBP.BattleMageAnimBP'"));
	if (!animationBlueprint.Succeeded())
		UE_LOG(LogSkeletalMesh, Error, TEXT("Summoner AnimBP Not Loaded"));
	GetMesh()->SetAnimInstanceClass(animationBlueprint.Object->GeneratedClass);

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
	Navigation->SetGoal(FVector(10000.0,0.0,0.0));
}
