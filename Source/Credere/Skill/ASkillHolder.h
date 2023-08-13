// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ASkillHolder.generated.h"


UCLASS()
class CREDERE_API ASkillHolder : public AActor
{
	GENERATED_BODY()

public:	
	ASkillHolder();

protected:
	virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor *OtherActor) override;
    virtual void NotifyActorEndOverlap(AActor *OtherActor) override;

public:	
	virtual void Tick(float DeltaTime) override;
	void SetStatHolder(const class AStatHolder* statHolder);
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USphereComponent> SphereComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UAutoAttackSkill> AutoAttackSkill;

	TObjectPtr<const class AStatHolder> StatHolder;

	TObjectPtr<const AActor> TargetingActor; 
};
