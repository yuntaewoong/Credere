// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enum/ECustomStatType.h"
#include "AStatHolder.generated.h"

UCLASS()
class CREDERE_API AStatHolder : public AActor
{
	GENERATED_BODY()

public:	
	AStatHolder();

protected:
	virtual void BeginPlay() override;
public:	
	void SetStatActive(ECustomStatType customStatType,bool isActive);
	class UHPStat* GetHpStat() const;
	class UAttackRadiusStat* GetAttackRadiusStat() const;
private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* EmptyComponent;

	UPROPERTY(VisibleAnywhere)
	class UHPStat* HpStat;
	
	UPROPERTY(VisibleAnywhere)
	class UAttackRadiusStat* AttackRadiusStat;

};
