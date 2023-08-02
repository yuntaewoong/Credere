// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/AHumanPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstanceSubsystem\UPlayableCharacterSubsystem.h"

AHumanPlayerController::AHumanPlayerController()
	:
	Super::APlayerController(),
	DefaultMappingContext(nullptr),
	CharacterForwardChangeAction(nullptr),
	CharacterBackwardChangeAction(nullptr)
{
	{//mapping context 로드
		static const ConstructorHelpers::FObjectFinder<UInputMappingContext> controllerInputMappingContext(TEXT("InputMappingContext'/Game/Inputs/PlayerControllerInputMappingContext.PlayerControllerInputMappingContext'"));
		if (!controllerInputMappingContext.Succeeded())
			UE_LOG(LogActor, Error, TEXT("PlayerControllerInput MappingContext Not Loaded"));
		DefaultMappingContext = controllerInputMappingContext.Object;
	}
	{//input action 로드
		static const ConstructorHelpers::FObjectFinder<UInputAction> characterForwardChangeAction(TEXT("InputAction'/Game/Inputs/InputActions/IA_CharacterForwardChange.IA_CharacterForwardChange'"));
		if (!characterForwardChangeAction.Succeeded())
			UE_LOG(LogActor, Error, TEXT("CharacterChangeAction Not Loaded"));
		CharacterForwardChangeAction = characterForwardChangeAction.Object;
		
		static const ConstructorHelpers::FObjectFinder<UInputAction> characterBackwardChangeAction(TEXT("InputAction'/Game/Inputs/InputActions/IA_CharacterBackwardChange.IA_CharacterBackwardChange'"));
		if (!characterBackwardChangeAction.Succeeded())
			UE_LOG(LogActor, Error, TEXT("CharacterChangeAction Not Loaded"));
		CharacterBackwardChangeAction = characterBackwardChangeAction.Object;
	
	}
}

void AHumanPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UEnhancedInputLocalPlayerSubsystem* subsystem = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>
		(
			GetLocalPlayer()
		);
	if (!subsystem)
	{
		UE_LOG(LogActor,Error,TEXT("SubSystem Not Setted"));
		return;
	}
	subsystem->AddMappingContext(DefaultMappingContext, 0);
}

void AHumanPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AHumanPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	if(!enhancedInputComponent)
	{
		UE_LOG(LogActor,Error,TEXT("InputComponent is null"));
		return;
	}
	enhancedInputComponent->BindAction(CharacterForwardChangeAction, ETriggerEvent::Started, this, &AHumanPlayerController::ChangeCharacterForward);
	enhancedInputComponent->BindAction(CharacterBackwardChangeAction, ETriggerEvent::Started, this, &AHumanPlayerController::ChangeCharacterBackward);
}

void AHumanPlayerController::ChangeCharacterForward()
{	
	if (UGameInstance* gameInstance = UGameplayStatics::GetGameInstance(this))
	{
		if (UPlayableCharacterSubsystem* playableCharacterSubsystem = 
			gameInstance->GetSubsystem<UPlayableCharacterSubsystem>())
		{
			if(!playableCharacterSubsystem->ChangeCharacterForward())
			{
				UE_LOG(LogController,Error,TEXT("Change Character Forward Failed"));
			}
		}
	}
}

void AHumanPlayerController::ChangeCharacterBackward()
{
	if (UGameInstance* gameInstance = UGameplayStatics::GetGameInstance(this))
	{
		if (UPlayableCharacterSubsystem* playableCharacterSubsystem = 
			gameInstance->GetSubsystem<UPlayableCharacterSubsystem>())
		{
			if(!playableCharacterSubsystem->ChangeCharacterBackward())
			{
				UE_LOG(LogController,Error,TEXT("Change Character Backward Failed"));
			}
		}
	}
}
