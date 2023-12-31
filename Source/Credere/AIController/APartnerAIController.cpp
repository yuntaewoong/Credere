// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController/APartnerAIController.h"
#include "PlayableCharacter\ABasePlayableCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstanceSubsystem\UPlayableCharacterSubsystem.h"


const FName APartnerAIController::GoalKey(TEXT("Goal"));

APartnerAIController::APartnerAIController()
	:
	Super::ABaseAIController()
{
	//비헤이비어 트리 로드
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/AI/Partner/PartnerBT.PartnerBT'"));
	if (!BTObject.Succeeded())
		UE_LOG(LogController,Error,TEXT("PartnerBT Not Loaded"));
	BehaviorTree = BTObject.Object;

	//블랙보드 로드
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("BlackboardData'/Game/AI/Partner/PartnerBB.PartnerBB'"));
	if (!BBObject.Succeeded())
		UE_LOG(LogController,Error,TEXT("PartnerBB Not Loaded"));
	BlackBoardData = BBObject.Object;
}

void APartnerAIController::Tick(float DeltaTime)
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
	const ABasePlayableCharacter* controlledCharacter = Cast<ABasePlayableCharacter>(GetPawn());
	if(controlledCharacter)
	{//리더 캐릭터를 목적지로 설정
		Blackboard->SetValueAsVector(GoalKey, leaderLocation - (leaderForwardVector+leaderRightVector) * 300);
	}
}


