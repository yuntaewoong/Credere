// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enum\ESkillType.h"
#include "ASkillHolder.generated.h"


UCLASS()
class CREDERE_API ASkillHolder : public AActor
{
	GENERATED_BODY()

public:	
	ASkillHolder();

protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
	void SetSkillActive(ESkillType customSkillType,bool isActive);
	void SetStatHolder(const class AStatHolder* statHolder);
private:
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere)
	class UBaseSkill* Skills[static_cast<uint8>(ESkillType::ITEM_NUM)];

	const class AStatHolder* StatHolder;
};
