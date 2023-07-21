// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UNavigationComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CREDERE_API UNavigationComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UNavigationComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetGoal(FVector goal);

private:
	UPROPERTY(VisibleAnywhere)
	class USplineComponent* RouteSpline;

	UPROPERTY(VisibleAnywhere)
	TArray<class USplineMeshComponent*> RouteSplineMeshes;

	FVector GoalLocation;

	uint16 MaxNumOfSplinePoints;

		
};
