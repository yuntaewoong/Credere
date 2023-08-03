// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AWarriorCharacter.h"
#include "Navigation/UNavigationComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstanceSubsystem\UPlayableCharacterSubsystem.h"

AWarriorCharacter::AWarriorCharacter()
	: 
	Super::ABasePlayableCharacter(),
	Navigation(nullptr),
	SkeletalMeshZAdjust(-80.0),
	SkeletalMeshYawAdjust(-90.0)
{
	//Navigation Component 
	Navigation = CreateDefaultSubobject<UNavigationComponent>(TEXT("Navigation"));
	Navigation->SetupAttachment(RootComponent);

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
	Navigation->SetGoal(FVector(10000.0,0.0,0.0));
	if (UGameInstance* gameInstance = UGameplayStatics::GetGameInstance(this))
	{
		if (UPlayableCharacterSubsystem* playableCharacterSubsystem = 
			gameInstance->GetSubsystem<UPlayableCharacterSubsystem>())
		{//GameInstance의  PlayableCharacterSubsystem에 본인이 리더인지 물어봄
			if(playableCharacterSubsystem->IsLeader(*this))
			{//리더일때만 네비게이션 컴포넌트 On
				Navigation->SetActive(true);	
			}
			else
			{
				Navigation->SetActive(false);
			}
		}
	}
}
