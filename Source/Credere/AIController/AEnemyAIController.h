// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController/ABaseAIController.h"
#include "AEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class CREDERE_API AEnemyAIController : public ABaseAIController
{
	GENERATED_BODY()
public:
	AEnemyAIController();
	virtual void Tick(float DeltaTime) override;
private:
	static const FName GoalKey;
};
