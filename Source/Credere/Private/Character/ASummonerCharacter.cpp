// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ASummonerCharacter.h"

ASummonerCharacter::ASummonerCharacter()
	:
	Super::ABaseCharacter(),
	SkeletalMeshZAdjust(-80.0),
	SkeletalMeshYawAdjust(-90.0)
{
	//SkeletalMesh로딩
	static const ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalMesh(TEXT("SkeletalMesh'/Game/ParagonShinbi/Characters/Heroes/Shinbi/Meshes/Shinbi.Shinbi'"));
	if (!skeletalMesh.Succeeded())
		UE_LOG(LogSkeletalMesh, Error, TEXT("Summoner Skeletal Mesh Not Loaded"));
	GetMesh()->SetSkeletalMesh(skeletalMesh.Object);
		
	//Animation Blueprint로딩
	static const ConstructorHelpers::FObjectFinder<UAnimBlueprint> animationBlueprint(TEXT("AnimBlueprint'/Game/Blueprints/AnimationBlueprints/SummonerAnimBP.SummonerAnimBP'"));
	if (!animationBlueprint.Succeeded())
		UE_LOG(LogSkeletalMesh, Error, TEXT("Summoner AnimBP Not Loaded"));
	GetMesh()->SetAnimInstanceClass(animationBlueprint.Object->GeneratedClass);

	GetMesh()->AddRelativeLocation(FVector(0.0, 0.0, SkeletalMeshZAdjust));
	GetMesh()->AddRelativeRotation(FQuat(FRotator(0.0,SkeletalMeshYawAdjust,0.0)));
}

void ASummonerCharacter::BeginPlay()
{	
	SpawnDefaultController();
	Super::BeginPlay();
	
}

void ASummonerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
