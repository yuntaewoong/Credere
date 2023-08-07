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
	void SetSkillActive(ESkillType customSkillType,bool isActive);
private:
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereComponent;
	TStaticArray<class UBaseSkill*,static_cast<uint32>(ESkillType::ITEM_NUM)> Skills;
};
