// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstanceSubsystem\UPlayableCharacterSubsystem.h"
#include "Controller\APartnerAIController.h"

ABaseCharacter::ABaseCharacter()
	:   
	Super::ACharacter(),
	CameraBoom(nullptr),
	FollowCamera(nullptr),
	DefaultMappingContext(nullptr),
	JumpAction(nullptr),
	MoveAction(nullptr),
	LookAction(nullptr)
{
	{//mapping context 로드
		static const ConstructorHelpers::FObjectFinder<UInputMappingContext> mappingContext(TEXT("InputMappingContext'/Game/Inputs/PlayerInputMappingContext.PlayerInputMappingContext'"));
		if (mappingContext.Succeeded())
			DefaultMappingContext = mappingContext.Object;
		else
			UE_LOG(LogActor, Error, TEXT("Player MappingContext Not Loaded"));
	}
	{//input action들 로드
		static const ConstructorHelpers::FObjectFinder<UInputAction> jumpAction(TEXT("InputAction'/Game/Inputs/InputActions/IA_Jump.IA_Jump'"));
		if (jumpAction.Succeeded())
			JumpAction = jumpAction.Object;
		else
			UE_LOG(LogActor, Error, TEXT("Jump Action Not Loaded"));

		static const ConstructorHelpers::FObjectFinder<UInputAction> moveAction(TEXT("InputAction'/Game/Inputs/InputActions/IA_Move.IA_Move'"));
		if (moveAction.Succeeded())
			MoveAction = moveAction.Object;
		else
			UE_LOG(LogActor, Error, TEXT("Move Action Not Loaded"));

		static const ConstructorHelpers::FObjectFinder<UInputAction> lookAction(TEXT("InputAction'/Game/Inputs/InputActions/IA_Look.IA_Look'"));
		if (lookAction.Succeeded())
			LookAction = lookAction.Object;
		else
			UE_LOG(LogActor, Error, TEXT("Look Action Not Loaded"));
	}
	PrimaryActorTick.bCanEverTick = true;//Tick On

	{//캐릭터의 회전이 Controller의 회전에 영향받지 않게 설정
		bUseControllerRotationPitch = false;
		bUseControllerRotationYaw = false;
		bUseControllerRotationRoll = false;
	}
	{//Character Movement Component파라미터 설정
		GetCharacterMovement()->bOrientRotationToMovement = true;//이동방향으로 회전하게 설정	
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 300.0f, 0.0f); //회전 가속도 설정
		GetCharacterMovement()->JumpZVelocity = 700.f;
		GetCharacterMovement()->AirControl = 0.35f;
		GetCharacterMovement()->GravityScale = 2.0f;
		GetCharacterMovement()->MaxWalkSpeed = 500.f;
		GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
		GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	}
	{//CameraBoom설정
		CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
		CameraBoom->SetupAttachment(RootComponent);
		CameraBoom->TargetArmLength = 400.0f; 
		CameraBoom->bUsePawnControlRotation = true;//Controller의 Rotation값 사용
	}
	{//FollowCamera설정
		FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
		FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
		FollowCamera->bUsePawnControlRotation = false;//Camera는 CameraBoom에 종속되므로 따로 회전 x
	}
	{//AI Controller설정
		AIControllerClass = APartnerAIController::StaticClass();
		AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	}
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (UGameInstance* gameInstance = UGameplayStatics::GetGameInstance(this))
	{
		if (UPlayableCharacterSubsystem* playableCharacterSubsystem = 
			gameInstance->GetSubsystem<UPlayableCharacterSubsystem>())
		{//GameInstance의  PlayableCharacterSubsystem에 캐릭터 등록
			playableCharacterSubsystem->AddPlayer(*this);
		}
	}

	APlayerController* playerController = Cast<APlayerController>(Controller);
	if (!playerController)
	{
		UE_LOG(LogActor,Warning,TEXT("Human Player Controller Not Setted"));
		return;
	}
	UEnhancedInputLocalPlayerSubsystem* subsystem = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>
		(
			playerController->GetLocalPlayer()
		);
	if (!subsystem)
	{
		UE_LOG(LogActor,Error,TEXT("SubSystem Not Setted"));
		return;
	}
	subsystem->AddMappingContext(DefaultMappingContext, 0);
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if(!enhancedInputComponent)
	{
		UE_LOG(LogActor,Error,TEXT("PlayerInputComponent is null"));
		return;
	}
	enhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	enhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Move);
	enhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Look);
}


void ABaseCharacter::Move(const FInputActionValue& Value)
{
	FVector2D movementVector = Value.Get<FVector2D>();//FVector2D인풋데이터
	if (Controller == nullptr)
	{
		UE_LOG(LogActor,Error,TEXT("Tried To Move But PlayerController Not Detected"));
		return;
	}
	const FRotator rotation = Controller->GetControlRotation();
	const FRotator yawRotation(0, rotation.Yaw, 0);
	const FVector forwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	const FVector rightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(forwardDirection, movementVector.Y);
	AddMovementInput(rightDirection, movementVector.X);
}

void ABaseCharacter::Look(const FInputActionValue& Value)
{
	FVector2D lookAxisVector = Value.Get<FVector2D>();
	if (Controller == nullptr)
	{
		UE_LOG(LogActor,Error,TEXT("Tried To Look But PlayerController Not Detected"));
		return;
	}
	AddControllerYawInput(lookAxisVector.X);
	AddControllerPitchInput(lookAxisVector.Y);
}

