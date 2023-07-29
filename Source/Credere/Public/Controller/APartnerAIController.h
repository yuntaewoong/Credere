// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "APartnerAIController.generated.h"

/**
 * 
 */
UCLASS()
class CREDERE_API APartnerAIController : public AAIController
{
	GENERATED_BODY()

public:
	APartnerAIController();
	
	virtual void Tick(float DeltaTime) override;
	virtual void OnPossess(APawn* InPawn) override;
	void RunAI(APawn* InPawn);
private:
	static const FName GoalKey;

	UPROPERTY(VisibleAnywhere)
	class UBehaviorTree* PartnerBT;

	UPROPERTY(VisibleAnywhere)
	class UBlackboardData* PartnerBB;
	
};
