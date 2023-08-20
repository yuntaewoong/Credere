// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ATriggerDetector.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTriggerDetector, Log, All);

UCLASS()
class CREDERE_API ATriggerDetector : public AActor
{
	GENERATED_BODY()
	
public:	
	ATriggerDetector();
	
	TObjectPtr<const AActor> GetOverlappedOpponent() const;
protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USphereComponent> SphereComponent;

	TObjectPtr<const AActor> OverlappedActor;

	float DetectingRadius;
};
