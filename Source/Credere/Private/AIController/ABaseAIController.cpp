// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController/ABaseAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

ABaseAIController::ABaseAIController()
	:
	Super::AAIController(),
	PartnerBT(nullptr),
	PartnerBB(nullptr)
{

}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunAI();
	//UE_LOG(LogController,Warning,TEXT("Partner Controller OnPossess Called"));
}

void ABaseAIController::OnUnPossess()
{	
	Super::OnUnPossess();
	StopAI();
	//UE_LOG(LogController,Warning,TEXT("Partner Controller OnUnPossess Called"));
}

void ABaseAIController::Initialize(FString btLocation, FString bbLocation)
{
	//비헤이비어 트리 로드
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(*btLocation);
	if (!BTObject.Succeeded())
		UE_LOG(LogController,Error,TEXT("PartnerBT Not Loaded"));
	PartnerBT = BTObject.Object;

	//블랙보드 로드
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(*bbLocation);
	if (!BBObject.Succeeded())
		UE_LOG(LogController,Error,TEXT("PartnerBB Not Loaded"));
	PartnerBB = BBObject.Object;
}

void ABaseAIController::RunAI()
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

void ABaseAIController::StopAI()
{
	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (!BehaviorTreeComponent)
	{
		UE_LOG(LogController,Warning,TEXT("Cannot find btComponent"));
		return;
	}
	BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
}
