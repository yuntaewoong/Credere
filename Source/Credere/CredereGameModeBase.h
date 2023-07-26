// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CredereGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CREDERE_API ACredereGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACredereGameModeBase(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
private:
	double spawnDistanceBetweenCharacters;
};
