// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;//Tick On

	{//캐릭터의 회전이 Controller의 회전에 영향받지 않게 설정
		bUseControllerRotationPitch = false;
		bUseControllerRotationYaw = false;
		bUseControllerRotationRoll = false;
	}
	{//Character Movement Component파라미터 설정
		GetCharacterMovement()->bOrientRotationToMovement = true;//이동방향으로 회전하게 설정	
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); //회전 가속도 설정
		GetCharacterMovement()->JumpZVelocity = 700.f;
		GetCharacterMovement()->AirControl = 0.35f;
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
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

