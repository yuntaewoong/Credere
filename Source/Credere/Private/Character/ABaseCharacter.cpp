// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;//Tick On

	{//ĳ������ ȸ���� Controller�� ȸ���� ������� �ʰ� ����
		bUseControllerRotationPitch = false;
		bUseControllerRotationYaw = false;
		bUseControllerRotationRoll = false;
	}
	{//Character Movement Component�Ķ���� ����
		GetCharacterMovement()->bOrientRotationToMovement = true;//�̵��������� ȸ���ϰ� ����	
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); //ȸ�� ���ӵ� ����
		GetCharacterMovement()->JumpZVelocity = 700.f;
		GetCharacterMovement()->AirControl = 0.35f;
		GetCharacterMovement()->MaxWalkSpeed = 500.f;
		GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
		GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	}
	{//CameraBoom����
		CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
		CameraBoom->SetupAttachment(RootComponent);
		CameraBoom->TargetArmLength = 400.0f; 
		CameraBoom->bUsePawnControlRotation = true;//Controller�� Rotation�� ���
	}
	{//FollowCamera����
		FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
		FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
		FollowCamera->bUsePawnControlRotation = false;//Camera�� CameraBoom�� ���ӵǹǷ� ���� ȸ�� x
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

