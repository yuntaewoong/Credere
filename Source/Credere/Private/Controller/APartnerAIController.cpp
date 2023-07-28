// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/APartnerAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

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

void APartnerAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UE_LOG(LogController,Warning,TEXT("APartnerPlayerController OnPossess Called"));
	RunAI();
}

void APartnerAIController::RunAI()
{
	UE_LOG(LogController,Warning,TEXT("Called RunAI"));
	UBlackboardComponent* bbComp = Blackboard;
	if (UseBlackboard(PartnerBB,bbComp))
	{
		RunBehaviorTree(PartnerBT);
	}
}
