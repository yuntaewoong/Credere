// Fill out your copyright notice in the Description page of Project Settings.


#include "Navigation\ANavigation.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Runtime/NavigationSystem/Public/NavigationPath.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"


ANavigation::ANavigation()
	:
	GoalLocation(FVector::Zero()),
	RouteSpline(nullptr),
	RouteSplineMeshes(TArray<USplineMeshComponent*>()),
	MaxNumOfSplinePoints(15u),
	SplineMeshTickness(0.1),
	RouteZHeight(40.0),
	bIsActive(false)
{
	PrimaryActorTick.bCanEverTick = true;

	{//Route Spline 생성
		RouteSpline = CreateDefaultSubobject<USplineComponent>(TEXT("Route Spline"));
		SetRootComponent(RouteSpline);
		RouteSpline->bDrawDebug = true;
	}
	{//Route Spline Mesh 생성
		static const ConstructorHelpers::FObjectFinder<UStaticMesh> splineStaticMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
		if (!splineStaticMesh.Succeeded())
			UE_LOG(LogActor, Error, TEXT("Cylinder Mesh Not Loaded"));
		static const ConstructorHelpers::FObjectFinder<UMaterialInterface> splineMeshMaterial(TEXT("Material'/Game/Materials/RouteMaterial.RouteMaterial'"));
		if (!splineMeshMaterial.Succeeded())
			UE_LOG(LogActor, Error, TEXT("Route Material Not Loaded"));

		RouteSplineMeshes.Reserve(MaxNumOfSplinePoints);
		for(uint16 i = 0;i<MaxNumOfSplinePoints;i++)
		{
			RouteSplineMeshes.Add(CreateDefaultSubobject<USplineMeshComponent>((*FString(TEXT("Spline Mesh") + FString::FromInt(i)))));
			RouteSplineMeshes[i]->SetStaticMesh(splineStaticMesh.Object);
			RouteSplineMeshes[i]->SetMaterial(0,splineMeshMaterial.Object);
			RouteSplineMeshes[i]->SetForwardAxis(ESplineMeshAxis::Z);
			RouteSplineMeshes[i]->SetStartScale(FVector2D(SplineMeshTickness,SplineMeshTickness));
			RouteSplineMeshes[i]->SetEndScale(FVector2D(SplineMeshTickness,SplineMeshTickness));
		}
	}
}
void ANavigation::BeginPlay()
{
	Super::BeginPlay();
}

void ANavigation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateSplineMeshes();
}

void ANavigation::SetActive(bool bNewActive)
{//네비게이션 액터를 비활성화할때 Spline Mesh 렌더여부와 길찾기 여부 전환
	bIsActive = bNewActive;
	for(auto splineMesh : RouteSplineMeshes)
	{	
		splineMesh->SetVisibility(bNewActive);
	}
}

void ANavigation::SetGoal(FVector goal)
{
	GoalLocation = goal;
}

//경로정보를 기반으로 새로운 Spline Mesh업데이트
void ANavigation::UpdateSplineMeshes()
{
	if(!bIsActive)//컴포넌트가 활성화되지 않으면 길찾기 연산 x
		return;
	if(!GetAttachParentActor())//부모 액터가 설정되지 않았다면 길찾기 연산 x
		return;
	const UNavigationSystemV1* navSys = UNavigationSystemV1::GetCurrent(GetWorld());
	const UNavigationPath* path = navSys->FindPathToLocationSynchronously(
		GetWorld(),
		GetAttachParentActor()->GetActorLocation(),
		GoalLocation,
		NULL
	);
	//UE_LOG(LogTemp,Log,TEXT("%s"),*path->GetDebugString());
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
			RouteSplineMeshes[i]->SetVisibility(false);
		}
	}
}

