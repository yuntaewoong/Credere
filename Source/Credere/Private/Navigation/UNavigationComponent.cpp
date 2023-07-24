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
	MaxNumOfSplinePoints(15u),
	SplineMeshTickness(0.4),
	RouteZHeight(40.0)
{
	PrimaryComponentTick.bCanEverTick = true;

	{//Route Spline 생성
		RouteSpline = CreateDefaultSubobject<USplineComponent>(TEXT("Route Spline"));
		RouteSpline->bDrawDebug = true;
		RouteSpline->SetupAttachment(this);
	}
	{//Route Spline Mesh 생성
		static const ConstructorHelpers::FObjectFinder<UStaticMesh> splineStaticMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
		if (!splineStaticMesh.Succeeded())
			UE_LOG(LogActor, Error, TEXT("Cylinder Mesh Not Loaded"));

		RouteSplineMeshes.Reserve(MaxNumOfSplinePoints);
		for(uint16 i = 0;i<MaxNumOfSplinePoints;i++)
		{
			RouteSplineMeshes.Add(CreateDefaultSubobject<USplineMeshComponent>((*FString(TEXT("Spline Mesh") + FString::FromInt(i)))));
			RouteSplineMeshes[i]->SetStaticMesh(splineStaticMesh.Object);
			RouteSplineMeshes[i]->SetForwardAxis(ESplineMeshAxis::Z);
			RouteSplineMeshes[i]->SetStartScale(FVector2D(SplineMeshTickness,SplineMeshTickness));
			RouteSplineMeshes[i]->SetEndScale(FVector2D(SplineMeshTickness,SplineMeshTickness));
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
	UpdateSplineMeshes();
}

void UNavigationComponent::SetGoal(FVector goal)
{
	GoalLocation = goal;
}

//경로정보를 기반으로 새로운 Spline Mesh업데이트
void UNavigationComponent::UpdateSplineMeshes()
{
	const UNavigationSystemV1* navSys = UNavigationSystemV1::GetCurrent(GetWorld());
	const UNavigationPath* path = navSys->FindPathToLocationSynchronously(
		GetWorld(),
		GetOwner()->GetActorLocation(),
		GoalLocation,
		NULL
	);
	UE_LOG(LogTemp,Log,TEXT("%s"),*path->GetDebugString());
	{//Spline 초기화 후 path정보에 따라 새로 업데이트
		RouteSpline->ClearSplinePoints();
		for(uint8 i = 0;i<path->PathPoints.Num();i++)
		{
			RouteSpline->AddSplinePoint(path->PathPoints[i] + FVector(0.0,0.0,RouteZHeight),ESplineCoordinateSpace::World);
		}
	}
	{//업데이트된 Spline정보로 Spline Mesh구성
		const uint8 numSplinePoints = RouteSpline->GetNumberOfSplinePoints();
		for(uint8 i = 0;i<RouteSpline->GetNumberOfSplineSegments();i++)
		{//Spline구역 Loop
			FVector splineStartPointLocation(FVector::Zero());
			FVector splineStartPointTangent(FVector::Zero());
			RouteSpline->GetLocationAndTangentAtSplinePoint(i,splineStartPointLocation,splineStartPointTangent,ESplineCoordinateSpace::World);

			FVector splineEndPointLocation(FVector::Zero());
			FVector splineEndPointTangent(FVector::Zero());
			RouteSpline->GetLocationAndTangentAtSplinePoint(i+1,splineEndPointLocation,splineEndPointTangent,ESplineCoordinateSpace::World);

			RouteSplineMeshes[i]->SetStartAndEnd(
				splineStartPointLocation,
				splineStartPointTangent,
				splineEndPointLocation,
				splineEndPointTangent,
				true
			);
		}
		for(uint8 i = RouteSpline->GetNumberOfSplineSegments();i<MaxNumOfSplinePoints-1;i++)
		{//쓰이지 않는 Spline Mesh는 안보이게 처리
			RouteSplineMeshes[i]->SetStartAndEnd(
				GetOwner()->GetActorLocation(),
				FVector::Zero(),
				GetOwner()->GetActorLocation(),
				FVector::Zero(),
				true
			);
		}
	}
}

