// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilitySystemHelpers/ATriggerDetector.h"
#include "Components/SphereComponent.h"
#include "PlayableCharacter\ABasePlayableCharacter.h"
#include "EnemyCharacter\ABaseEnemyCharacter.h"

DEFINE_LOG_CATEGORY(LogTriggerDetector);

ATriggerDetector::ATriggerDetector()
	:
	Super::AActor(),
	SphereComponent(nullptr),
	OverlappedActor(nullptr),
	DetectingRadius(250.f)
{
	PrimaryActorTick.bCanEverTick = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Capsule Collider"));
	RootComponent = SphereComponent;
	SphereComponent->bHiddenInGame = false;
	SphereComponent->SetSphereRadius(DetectingRadius);
}

TObjectPtr<const AActor> ATriggerDetector::GetOverlappedOpponent() const
{
	return OverlappedActor;
}

void ATriggerDetector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATriggerDetector::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATriggerDetector::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	AActor* parentActor = nullptr;
	parentActor = GetAttachParentActor();
	if(!parentActor)
	{
		UE_LOG(LogTriggerDetector,Warning,TEXT("TriggerDetector is not Set to Character Actor"));
		return;
	}
	if(
		parentActor->GetClass()->IsChildOf(ABasePlayableCharacter::StaticClass()) &&
		OtherActor->GetClass()->IsChildOf(ABaseEnemyCharacter::StaticClass()) ||
		OtherActor->GetClass()->IsChildOf(ABasePlayableCharacter::StaticClass()) &&
		parentActor->GetClass()->IsChildOf(ABaseEnemyCharacter::StaticClass())
	)
	{
	//case1. 부모가 Playable이고 OtherActor가 Enemy일 때
	//case2. 부모가 Enemy이고 OtherActor가 Playable일 때
		OverlappedActor = OtherActor;
		UE_LOG(LogTriggerDetector,Warning,TEXT("Opponent OverlapStart"));
	}
}

void ATriggerDetector::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	if(OverlappedActor != nullptr && OverlappedActor == OtherActor)
	{
		OverlappedActor = nullptr;
		UE_LOG(LogTriggerDetector,Warning,TEXT("Opponent OverlapEnd"));
	}
}


