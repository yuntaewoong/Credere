// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter/ABasePlayableCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Stat\AStatHolder.h"
#include "Skill\ASkillHolder.h"
#include "AbilitySystem\UCredereAbilitySystemComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstanceSubsystem\UPlayableCharacterSubsystem.h"
#include "Navigation\ANavigation.h"
#include "AIController\APartnerAIController.h"

ABasePlayableCharacter::ABasePlayableCharacter()
	:   
	Super::ACharacter(),
	Navigation(nullptr),
	StatHolder(nullptr),
	SkillHolder(nullptr),
	AbilitySystemComponent(nullptr),
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
	{//Ability System설정
		AbilitySystemComponent = CreateDefaultSubobject<UCredereAbilitySystemComponent>(TEXT("Ability System"));
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
}

void ABasePlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
	{//Navigation
		Navigation = GetWorld()->SpawnActor<ANavigation>(
			FVector::ZeroVector,
			FRotator::ZeroRotator
		);
		Navigation->AttachToActor(this,FAttachmentTransformRules::KeepRelativeTransform);
	}
	{//StatHolder스폰
		StatHolder = GetWorld()->SpawnActor<AStatHolder>(
			FVector::ZeroVector,
			FRotator::ZeroRotator
		);
		StatHolder->AttachToActor(this,FAttachmentTransformRules::KeepRelativeTransform);
	}
	{//SKillHolder스폰
		SkillHolder = GetWorld()->SpawnActor<ASkillHolder>(
			FVector::ZeroVector,
			FRotator::ZeroRotator
		);
		SkillHolder->AttachToActor(this,FAttachmentTransformRules::KeepRelativeTransform);
		//SkillHolder->SetSkillActive(ESkillType::AUTO_ATTACK,true);
		SkillHolder->SetStatHolder(StatHolder);//스킬홀더가 사용할 스탯홀더에 대한 포인터 전달
	}
	
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
	{//Player가 조작하는 캐릭터일때만 인풋등록
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

void ABasePlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Navigation->SetGoal(FVector(10000.0,0.0,0.0));
	if (UGameInstance* gameInstance = UGameplayStatics::GetGameInstance(this))
	{
		if (UPlayableCharacterSubsystem* playableCharacterSubsystem = 
			gameInstance->GetSubsystem<UPlayableCharacterSubsystem>())
		{//GameInstance의  PlayableCharacterSubsystem에 본인이 리더인지 물어봄
			if(playableCharacterSubsystem->IsLeader(*this))
			{//리더일때만 네비게이션 컴포넌트 On
				Navigation->SetActive(true);	
			}
			else
			{
				Navigation->SetActive(false);
			}
		}
	}
}

void ABasePlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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
	enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABasePlayableCharacter::Move);
	enhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABasePlayableCharacter::Look);
}


void ABasePlayableCharacter::Move(const FInputActionValue& Value)
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

void ABasePlayableCharacter::Look(const FInputActionValue& Value)
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

