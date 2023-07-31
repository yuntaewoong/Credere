// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UPlayableCharacterSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogGameInstance, Log, All);
/**
 * 
 */
UCLASS()
class CREDERE_API UPlayableCharacterSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UPlayableCharacterSubsystem();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;


	void AddPlayer(const class ABaseCharacter& Player);
	void SetLeader(const class ABaseCharacter& Player);
	const class ABaseCharacter& GetLeader() const;
	bool ChangeLeaderForward();
	bool ChangeLeaderBackward();
private:
	TArray<const class ABaseCharacter*> PlayableCharacters;
	const class ABaseCharacter* Leader;
};
