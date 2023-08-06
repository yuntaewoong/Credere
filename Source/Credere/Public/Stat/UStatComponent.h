// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enum/ECustomStatType.h"
#include "UStatComponent.generated.h"

//UENUM()
//enum class ECustomStatType : uint8
//{//모든 스탯들을 Enum으로 정리(StaticArray 초기화를 위해서 Stat추가시 마다 Enum추가도 필요)
//    HP,
//	ITEM_NUM
//};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CREDERE_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStatComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetStatActive(ECustomStatType customStatType,bool isActive);

private:
	TStaticArray<class UBaseStat*,static_cast<uint32>(ECustomStatType::ITEM_NUM)> Stats;
};
