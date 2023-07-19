// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ABaseCharacter.h"
#include "AWarriorCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CREDERE_API AWarriorCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	AWarriorCharacter();
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(VisibleAnywhere)
	class UNavigationComponent* Navigation;

	double SkeletalMeshZAdjust;
	double SkeletalMeshPitchAdjust;
	
};
