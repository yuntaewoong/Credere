// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
	class UHPStat* GetHpStat() const;
	class UAttackRadiusStat* GetAttackRadiusStat() const;
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> EmptyComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UHPStat> HpStat;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UAttackRadiusStat> AttackRadiusStat;

};
