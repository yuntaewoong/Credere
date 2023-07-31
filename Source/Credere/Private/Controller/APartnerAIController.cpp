// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/APartnerAIController.h"
#include "Character\ABaseCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstanceSubsystem\UPlayableCharacterSubsystem.h"


const FName APartnerAIController::GoalKey(TEXT("Goal"));

APartnerAIController::APartnerAIController()
	:
	Super::AAIController(),
	PartnerBT(nullptr),
	PartnerBB(nullptr)
{
	//비헤이비어 트리 로드
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/AI/Partner/PartnerBT.PartnerBT'"));
	if (!BTObject.Succeeded())
		UE_LOG(LogController,Error,TEXT("PartnerBT Not Loaded"));
	PartnerBT = BTObject.Object;

	//블랙보드 로드
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("BlackboardData'/Game/AI/Partner/PartnerBB.PartnerBB'"));
	if (!BBObject.Succeeded())
		UE_LOG(LogController,Error,TEXT("PartnerBB Not Loaded"));
	PartnerBB = BBObject.Object;
	
}

void APartnerAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector leaderLocation = FVector::Zero();
	FVector leaderForwardVector = FVector::Zero();
	if (UGameInstance* gameInstance = UGameplayStatics::GetGameInstance(this))
	{
		if (UPlayableCharacterSubsystem* playableCharacterSubsystem = 
			gameInstance->GetSubsystem<UPlayableCharacterSubsystem>())
		{//GameInstance의  PlayableCharacterSubsystem에서 리더정보 Get
			leaderLocation = playableCharacterSubsystem->GetLeader().GetActorLocation();
			leaderForwardVector = playableCharacterSubsystem->GetLeader().GetActorForwardVector();
		}
	}
	const ABaseCharacter* ownerCharacter = Cast<ABaseCharacter>(GetPawn());
	if(ownerCharacter)
	{//리더 캐릭터를 목적지로 설정
		Blackboard->SetValueAsVector(GoalKey, leaderLocation - leaderForwardVector * 100);
	}
}

void APartnerAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunAI(InPawn);
}

void APartnerAIController::RunAI(APawn* InPawn)
{
	UBlackboardComponent* bbComp = Blackboard;
	if (UseBlackboard(PartnerBB,bbComp))
	{
		if(!RunBehaviorTree(PartnerBT))
		{
			UE_LOG(LogController,Error,TEXT("RunBehaviorTree Not Called"));
		}
	}
}
