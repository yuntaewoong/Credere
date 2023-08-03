// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayableCharacter/ABasePlayableCharacter.h"
#include "AArcherCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CREDERE_API AArcherCharacter : public ABasePlayableCharacter
{
	GENERATED_BODY()
public:
	AArcherCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(VisibleAnywhere)
	class UNavigationComponent* Navigation;

	double SkeletalMeshZAdjust;
	double SkeletalMeshYawAdjust;
};
