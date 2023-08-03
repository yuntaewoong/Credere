// Copyright Epic Games, Inc. All Rights Reserved.


#include "CredereGameModeBase.h"
#include "PlayableCharacter\AWarriorCharacter.h"
#include "PlayableCharacter\AArcherCharacter.h"
#include "PlayableCharacter\ABattleMageCharacter.h"
#include "EnemyCharacter\ADualBladeEnemyCharacter.h"
#include "PlayerController\AHumanPlayerController.h"
#include "AIController\APartnerAIController.h"
#include "AIController\AEnemyAIController.h"
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
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABasePlayableCharacter::StaticClass(), FoundActors);
	for(auto iter : FoundActors)
	{//모든 BaseCharacter탐색
		if(AWarriorCharacter* defaultWarriorCharacter = Cast<AWarriorCharacter>(iter))
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
			FVector actorForwardVector = defaultWarriorCharacter->GetActorForwardVector();
			{//궁수 스폰 & AI컨트롤러 빙의
				AArcherCharacter* archerCharacter = GetWorld()->SpawnActor<AArcherCharacter>(
					defaultWarriorCharacter->GetActorLocation() + actorLeftVector * spawnDistanceBetweenCharacters,
					defaultWarriorCharacter->GetActorRotation()
				);
				APartnerAIController* partnerAIController = GetWorld()->SpawnActor<APartnerAIController>();
				partnerAIController->Possess(archerCharacter);
			}
			{//배틀메이지 스폰 & AI컨트롤러 빙의
				ABattleMageCharacter* battleMageCharacter = GetWorld()->SpawnActor<ABattleMageCharacter>(
					defaultWarriorCharacter->GetActorLocation() + actorRightVector * spawnDistanceBetweenCharacters,
					defaultWarriorCharacter->GetActorRotation()
				);
				APartnerAIController* partnerAIController = GetWorld()->SpawnActor<APartnerAIController>();
				partnerAIController->Possess(battleMageCharacter);
			}
			{//적 스폰 & AI컨트롤러 빙의
				ADualBladeEnemyCharacter* dualBladeEnemyCharacter = GetWorld()->SpawnActor<ADualBladeEnemyCharacter>(
					defaultWarriorCharacter->GetActorLocation() + actorForwardVector * spawnDistanceBetweenCharacters,
					defaultWarriorCharacter->GetActorRotation()
				);
				AEnemyAIController* enemyAIController = GetWorld()->SpawnActor<AEnemyAIController>();
				enemyAIController->Possess(dualBladeEnemyCharacter);
			}
			break;
		}
	}

	
}
