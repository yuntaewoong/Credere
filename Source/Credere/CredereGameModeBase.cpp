// Copyright Epic Games, Inc. All Rights Reserved.


#include "CredereGameModeBase.h"
#include "Character\AWarriorCharacter.h"
#include "PlayerController\HumanPlayerController.h"

ACredereGameModeBase::ACredereGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super::AGameModeBase(ObjectInitializer)
{
	DefaultPawnClass = AWarriorCharacter::StaticClass();
	PlayerControllerClass = AHumanPlayerController::StaticClass();
}
