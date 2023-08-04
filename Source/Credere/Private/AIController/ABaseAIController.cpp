// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController/ABaseAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

ABaseAIController::ABaseAIController()
	:
	Super::AAIController(),
	behaviorTree(nullptr),
	blackBoardData(nullptr)
{

}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunAI();
}

void ABaseAIController::OnUnPossess()
{	
	Super::OnUnPossess();
	StopAI();
}


void ABaseAIController::RunAI()
{
	UBlackboardComponent* bbComp = Blackboard;
	if (UseBlackboard(blackBoardData,bbComp))
	{
		if(!RunBehaviorTree(behaviorTree))
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
