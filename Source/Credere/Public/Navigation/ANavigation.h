// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ANavigation.generated.h"


UCLASS()
class CREDERE_API ANavigation : public AActor
{
	GENERATED_BODY()

public:	
	ANavigation();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	void SetActive(bool bNewActive);
	void SetGoal(FVector goal);

private:
	UPROPERTY(VisibleAnywhere)
	class USplineComponent* RouteSpline;

	UPROPERTY(VisibleAnywhere)
	TArray<class USplineMeshComponent*> RouteSplineMeshes;

	FVector GoalLocation;
	uint16 MaxNumOfSplinePoints;
	double SplineMeshTickness;
	double RouteZHeight;
	bool bIsActive;
private:
	void UpdateSplineMeshes();

		
};
