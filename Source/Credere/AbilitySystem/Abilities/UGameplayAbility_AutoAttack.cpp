// Fill out your copyright notice in the Description page of Project Settings.


#include "UGameplayAbility_AutoAttack.h"
#include "AbilitySystem\AbilitySystemHelpers\ATriggerDetector.h"
#include "Abilities/Tasks/AbilityTask_Repeat.h"

UGameplayAbility_AutoAttack::UGameplayAbility_AutoAttack()
	:
	Super::UBaseGameplayAbility(),
	AbilitySpecHandle(),
	AbilityActorInfo(nullptr),
	AbilityActivationInfo(),
	GE_DamageBPClass(nullptr),
	TriggerDetector(nullptr),
	RepeatAbilityTask(nullptr),
	AutoAttackInterval(5.0f),
	LastAttackTime(0)
{
	static ConstructorHelpers::FClassFinder<UGameplayEffect> damageGE(TEXT("Blueprint'/Game/Blueprints/GameplayEffectBlueprints/GE_DamageInstant.GE_DamageInstant'"));
	if(!damageGE.Succeeded())
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
	AbilitySpecHandle = Handle;
	AbilityActorInfo = ActorInfo;
	AbilityActivationInfo = ActivationInfo;
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
	LastAttackTime = FDateTime::Now();
	/*FGameplayAbilityTargetData targetData;
	FGameplayAbilityTargetDataHandle targetDataHandle;
	FGameplayAbilitySpec gameplayAbilitySpec;
	targetDataHandle.Add(&targetData);
	ApplyGameplayEffectToTarget(
		AbilitySpecHandle,
		AbilityActorInfo,
		AbilityActivationInfo,
		targetDataHandle,
		GE_DamageBPClass,
		1
	);*/
	
	UE_LOG(LogGameplayAbility,Warning,TEXT("Attack to Opponent"));
}