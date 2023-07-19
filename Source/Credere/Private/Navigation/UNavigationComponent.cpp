// Fill out your copyright notice in the Description page of Project Settings.


#include "Navigation\UNavigationComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Runtime/NavigationSystem/Public/NavigationPath.h"

UNavigationComponent::UNavigationComponent()
	:
	EndPoint(FVector::Zero())
{
	PrimaryComponentTick.bCanEverTick = true;
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

void UNavigationComponent::SetEndPoint(FVector endPoint)
{
	EndPoint = endPoint;
}

