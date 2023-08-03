// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ABaseAIController.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class CREDERE_API ABaseAIController : public AAIController
{
	GENERATED_BODY()
public:
	ABaseAIController();
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
protected:
	void Initialize(FString btLocation,FString bbLocation);
private:
	void RunAI();
	void StopAI();
private:
	UPROPERTY(VisibleAnywhere)
	class UBehaviorTree* PartnerBT;

	UPROPERTY(VisibleAnywhere)
	class UBlackboardData* PartnerBB;
};
