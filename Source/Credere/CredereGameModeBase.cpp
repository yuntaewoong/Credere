// Copyright Epic Games, Inc. All Rights Reserved.


#include "CredereGameModeBase.h"
#include "Character\AWarriorCharacter.h"
#include "Character\AArcherCharacter.h"
#include "Character\ABattleMageCharacter.h"
#include "Controller\AHumanPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstanceSubsystem\UPlayableCharacterSubsystem.h"

ACredereGameModeBase::ACredereGameModeBase(const FObjectInitializer& ObjectInitializer)
	: 
	Super::AGameModeBase(ObjectInitializer),
	spawnDistanceBetweenCharacters(100.0)
{
	DefaultPawnClass = AWarriorCharacter::StaticClass();
	PlayerControllerClass = AHumanPlayerController::StaticClass();
}

void ACredereGameModeBase::BeginPlay()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseCharacter::StaticClass(), FoundActors);
	for(auto iter : FoundActors)
	{//모든 BaseCharacter탐색
		if(const AWarriorCharacter* defaultWarriorCharacter = Cast<AWarriorCharacter>(iter))
		{//기본 캐릭터 발견 시
			if (UGameInstance* gameInstance = UGameplayStatics::GetGameInstance(this))
			{
				if (UPlayableCharacterSubsystem* playableCharacterSubsystem = 
					gameInstance->GetSubsystem<UPlayableCharacterSubsystem>())
				{//GameInstance의  PlayableCharacterSubsystem에 리더등록
					playableCharacterSubsystem->SetLeader(*defaultWarriorCharacter);
				}
			}
			FVector actorLeftVector = defaultWarriorCharacter->GetActorRightVector() * (-1);
			FVector actorRightVector = defaultWarriorCharacter->GetActorRightVector();
			AArcherCharacter* archerCharacter = GetWorld()->SpawnActor<AArcherCharacter>(
				defaultWarriorCharacter->GetActorLocation() + actorLeftVector * spawnDistanceBetweenCharacters,
				defaultWarriorCharacter->GetActorRotation()
			);//궁수 스폰
			ABattleMageCharacter* battleMageCharacter = GetWorld()->SpawnActor<ABattleMageCharacter>(
				defaultWarriorCharacter->GetActorLocation() + actorRightVector * spawnDistanceBetweenCharacters,
				defaultWarriorCharacter->GetActorRotation()
			);//배틀메이지 스폰
			break;
		}
	}

	
}
