// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController/AEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstanceSubsystem\UPlayableCharacterSubsystem.h"
#include "PlayableCharacter\ABasePlayableCharacter.h"
#include "EnemyCharacter\ABaseEnemyCharacter.h"

const FName AEnemyAIController::GoalKey(TEXT("Goal"));

AEnemyAIController::AEnemyAIController()
	:
	Super::ABaseAIController()
{
	Initialize(
		TEXT("BehaviorTree'/Game/AI/Enemy/EnemyBT.EnemyBT'"),
		TEXT("BlackboardData'/Game/AI/Enemy/EnemyBB.EnemyBB'")
	);
}
void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector leaderLocation = FVector::Zero();
	FVector leaderForwardVector = FVector::Zero();
	FVector leaderRightVector = FVector::Zero();
	if (UGameInstance* gameInstance = UGameplayStatics::GetGameInstance(this))
	{
		if (UPlayableCharacterSubsystem* playableCharacterSubsystem = 
			gameInstance->GetSubsystem<UPlayableCharacterSubsystem>())
		{//GameInstance의  PlayableCharacterSubsystem에서 리더정보 Get
			leaderLocation = playableCharacterSubsystem->GetLeader().GetActorLocation();
			leaderForwardVector = playableCharacterSubsystem->GetLeader().GetActorForwardVector();
			leaderRightVector = playableCharacterSubsystem->GetLeader().GetActorRightVector();
		}
	}
	const ABaseEnemyCharacter* controlledCharacter = Cast<ABaseEnemyCharacter>(GetPawn());
	if(controlledCharacter)
	{//리더 캐릭터를 목적지로 설정
		Blackboard->SetValueAsVector(GoalKey, leaderLocation + (leaderForwardVector+leaderRightVector) * 300);
	}
}
