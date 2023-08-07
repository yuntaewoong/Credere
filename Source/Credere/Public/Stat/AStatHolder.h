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

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* emptyComponent;
	TStaticArray<class UBaseStat*,static_cast<uint32>(ECustomStatType::ITEM_NUM)> Stats;
	
};
