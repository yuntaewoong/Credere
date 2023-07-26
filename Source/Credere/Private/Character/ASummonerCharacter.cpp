// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ASummonerCharacter.h"

ASummonerCharacter::ASummonerCharacter()
	:
	Super::ABaseCharacter()
{
	//SkeletalMesh로딩
	static const ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalMesh(TEXT("SkeletalMesh'/Game/ParagonShinbi/Characters/Heroes/Shinbi/Meshes/Shinbi.Shinbi'"));
	if (!skeletalMesh.Succeeded())
		UE_LOG(LogSkeletalMesh, Error, TEXT("Summoner Skeletal Mesh Not Loaded"));
	GetMesh()->SetSkeletalMesh(skeletalMesh.Object);
		
	
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
