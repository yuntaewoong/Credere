// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/AHumanPlayerController.h"

AHumanPlayerController::AHumanPlayerController()
{
	
}

void AHumanPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UE_LOG(LogController,Warning,TEXT("AHumanPlayerController OnPossess Called"));
}
