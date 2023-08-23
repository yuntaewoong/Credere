// Fill out your copyright notice in the Description page of Project Settings.


#include "UGameplayAbility_AutoAttack.h"
#include "AbilitySystem\AbilitySystemHelpers\ATriggerDetector.h"
#include "Abilities/Tasks/AbilityTask_Repeat.h"
#include "PlayableCharacter/ABasePlayableCharacter.h"
#include "Kismet/KismetMathLibrary.h"

UGameplayAbility_AutoAttack::UGameplayAbility_AutoAttack()
	:
	Super::UBaseGameplayAbility(),
	GE_DamageBPClass(nullptr),
	TriggerDetector(nullptr),
	RepeatAbilityTask(nullptr),
	AutoAttackInterval(5.0f),
	LastAttackTime(0)
{
	static ConstructorHelpers::FClassFinder<UGameplayEffect> damageGE(TEXT("Blueprint'/Game/Blueprints/GameplayEffectBlueprints/GE_DamageInstant.GE_DamageInstant_C'"));
	if(!damageGE.Succeeded() || !damageGE.Class )
		UE_LOG(LogGameplayAbility,Warning,TEXT("Can not find GE_Damage Class"));
	GE_DamageBPClass = damageGE.Class;
}

bool UGameplayAbility_AutoAttack::CanActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayTagContainer* SourceTags, 
	const FGameplayTagContainer* TargetTags,
	OUT FGameplayTagContainer* OptionalRelevantTags
) const
{
	return Super::CanActivateAbility(Handle,ActorInfo,SourceTags,TargetTags,OptionalRelevantTags);
}

void UGameplayAbility_AutoAttack::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData
)
{
	if(!TriggerDetector)
	{//Trigger Detector 스폰, 위치 업데이트를 위해 어빌리티 소유자에게 Attach
		FVector spawnLocation = FVector::ZeroVector;
		FRotator spawnRotation = FRotator::ZeroRotator;
		TriggerDetector = GetWorld()->SpawnActor<ATriggerDetector>(spawnLocation,spawnRotation);
		TriggerDetector->AttachToActor(ActorInfo->AvatarActor.Get(),FAttachmentTransformRules::KeepRelativeTransform);
	}
	RepeatAbilityTask = UAbilityTask_Repeat::RepeatAction(this,AutoAttackInterval,MAX_int32);//5초마다 Action반복, CancleAbility할때까지 무한 반복(MAX_INT32로 표현)
	RepeatAbilityTask->OnPerformAction.AddDynamic(this,&UGameplayAbility_AutoAttack::AttackRepeat);
	RepeatAbilityTask->ReadyForActivation();

	UE_LOG(LogGameplayAbility,Warning,TEXT("AutoAttack Ability Activated"));
	Super::ActivateAbility(Handle,ActorInfo,ActivationInfo,TriggerEventData);
}

void UGameplayAbility_AutoAttack::EndAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, 
	bool bWasCancelled
)
{
	UE_LOG(LogGameplayAbility,Warning,TEXT("AutoAttack Ability Ended"));
	Super::EndAbility(Handle,ActorInfo,ActivationInfo,bReplicateEndAbility,bWasCancelled);
}

void UGameplayAbility_AutoAttack::AttackRepeat(int32 ActionNumber)
{
	const AActor* overlappedOpponent = TriggerDetector->GetOverlappedOpponent();
	if(overlappedOpponent)
	{
		Attack();
	}
}

void UGameplayAbility_AutoAttack::Attack()
{
	AActor* targetActor = TriggerDetector->GetOverlappedOpponent();
	if(!targetActor)
		return;//TriggerDetector에 감지된 상대방이 없으면 공격 x
	LastAttackTime = FDateTime::Now();
	ApplyDamageGameplayEffectToOpponent(targetActor);
	RotatePlayerToOpponent(targetActor);
	PlayAttack1Montage();
}

void UGameplayAbility_AutoAttack::ApplyDamageGameplayEffectToOpponent(AActor* OverlappedOpponent)
{//TargetData생성후 GE적용, new로 생성한 TargetData는 TargetDataHandle의 TSharedPtr로 관리되기에 메모리 누수가 일어나지 않음
	FGameplayAbilityTargetDataHandle targetDataHandle;
	FGameplayAbilityTargetData_ActorArray* pTargetData = new FGameplayAbilityTargetData_ActorArray();
	pTargetData->TargetActorArray.Add(OverlappedOpponent);
	targetDataHandle.Add(pTargetData);
	ApplyGameplayEffectToTarget(
		CurrentSpecHandle, 
		CurrentActorInfo,
		CurrentActivationInfo,
		targetDataHandle, 
		GE_DamageBPClass,
		1
	);
}

void UGameplayAbility_AutoAttack::RotatePlayerToOpponent(const AActor* OverlappedOpponent) const
{//적을 향하도록 플레이어 회전(Yaw값만)
	ABasePlayableCharacter* playerCharacter =  Cast<ABasePlayableCharacter>(CurrentActorInfo->AvatarActor);
	if(playerCharacter)
	{
		FRotator enemyLookingRotator = UKismetMathLibrary::FindLookAtRotation(
			playerCharacter->GetActorLocation(),
			OverlappedOpponent->GetActorLocation()
		);
		enemyLookingRotator.Roll = 0.0;
		enemyLookingRotator.Pitch = 0.0;
		playerCharacter->SetActorRotation(FQuat::MakeFromRotator(enemyLookingRotator));
	}
}

void UGameplayAbility_AutoAttack::PlayAttack1Montage() const
{//플레이어 공격 몽타주 재생
	ABasePlayableCharacter* playerCharacter =  Cast<ABasePlayableCharacter>(CurrentActorInfo->AvatarActor);
	if(playerCharacter)
	{
		UAnimInstance* playerAnimInstance = CurrentActorInfo->GetAnimInstance();
		if(playerAnimInstance)
		{
			playerAnimInstance->Montage_Play(playerCharacter->GetAttack1AnimMontage());
		}
	}
}
