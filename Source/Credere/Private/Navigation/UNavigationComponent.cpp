// Fill out your copyright notice in the Description page of Project Settings.


#include "Navigation\UNavigationComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Runtime/NavigationSystem/Public/NavigationPath.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"


UNavigationComponent::UNavigationComponent()
	:
	GoalLocation(FVector::Zero()),
	RouteSpline(nullptr),
	RouteSplineMeshes(TArray<USplineMeshComponent*>()),
	MaxNumOfSplinePoints(5u)
{
	PrimaryComponentTick.bCanEverTick = true;
	{//Route Spline 생성
		RouteSpline = CreateDefaultSubobject<USplineComponent>(TEXT("Route Spline"));
		RouteSpline->SetupAttachment(this);
	}
	{//Route Spline Mesh 생성
		RouteSplineMeshes.Reserve(MaxNumOfSplinePoints);
		for(uint16 i = 0;i<MaxNumOfSplinePoints;i++)
		{
			RouteSplineMeshes.Add(CreateDefaultSubobject<USplineMeshComponent>((*FString("Name" + FString::FromInt(i)))));
			RouteSplineMeshes[i]->SetupAttachment(RouteSpline);
		}
	}
}
void UNavigationComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UNavigationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UNavigationSystemV1* navSys = UNavigationSystemV1::GetCurrent(GetWorld());
	UNavigationPath* path = navSys->FindPathToLocationSynchronously(
		GetWorld(),
		GetOwner()->GetActorLocation(),
		FVector::Zero(),
		NULL
	);
	UE_LOG(LogTemp,Log,TEXT("%s"),*path->GetDebugString());
	for(int i= 0;i<path->PathPoints.Num();i++)
	{
		UE_LOG(LogTemp,Log,TEXT("PathPoint %d %s"),i,*path->PathPoints[i].ToString());
	}
	
}

void UNavigationComponent::SetGoal(FVector goal)
{
	GoalLocation = goal;
}

