// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UNavigationComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CREDERE_API UNavigationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UNavigationComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetActive(bool bNewActive,bool bReset = false) override;
	void SetGoal(FVector goal);

private:
	UPROPERTY()
	class USplineComponent* RouteSpline;

	UPROPERTY()
	TArray<class USplineMeshComponent*> RouteSplineMeshes;

	FVector GoalLocation;
	uint16 MaxNumOfSplinePoints;
	double SplineMeshTickness;
	double RouteZHeight;
	bool bIsActive;
private:
	void UpdateSplineMeshes();

		
};
