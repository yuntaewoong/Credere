// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController/ABaseAIController.h"
#include "APartnerAIController.generated.h"

/**
 * 
 */
UCLASS()
class CREDERE_API APartnerAIController : public ABaseAIController
{
	GENERATED_BODY()

public:
	APartnerAIController();
	virtual void Tick(float DeltaTime) override;
private:
	static const FName GoalKey;
	
};
