// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstanceSubsystem/UPlayableCharacterSubsystem.h"
#include "Character\ABaseCharacter.h"


DEFINE_LOG_CATEGORY(LogGameInstance);

UPlayableCharacterSubsystem::UPlayableCharacterSubsystem()
	:
	Super::UGameInstanceSubsystem(),
	PlayableCharacters(TArray<ABaseCharacter*>()),
	Leader(nullptr)
{
}

void UPlayableCharacterSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

}

void UPlayableCharacterSubsystem::Deinitialize()
{
}

void UPlayableCharacterSubsystem::AddPlayer(const ABaseCharacter& Player)
{
	PlayableCharacters.Add(&Player);
}

void UPlayableCharacterSubsystem::SetLeader(const ABaseCharacter& Player)
{
	Leader = &Player;
}

const ABaseCharacter& UPlayableCharacterSubsystem::GetLeader() const
{
	return *Leader;
}

bool UPlayableCharacterSubsystem::ChangeLeaderForward()
{//정방향으로 리더전환 ex/ 1 , 2(리더), 3 -> 1,2,3(리더)
	int32 leaderIndex = 0;
	if(!PlayableCharacters.Find(Leader,leaderIndex))
	{
		UE_LOG(LogGameInstance,Warning,TEXT("Leader Not Existed"));
		return false;
	}
	int32 newLeaderIndex = (leaderIndex + 1) % PlayableCharacters.Num();
	Leader = PlayableCharacters[newLeaderIndex];
	return true;
}

bool UPlayableCharacterSubsystem::ChangeLeaderBackward()
{//역방향으로 리더전환 ex/ 1, 2(리더),3->1(리더),2,3
	int32 leaderIndex = 0;
	if(!PlayableCharacters.Find(Leader,leaderIndex))
	{
		UE_LOG(LogGameInstance,Warning,TEXT("Leader Not Existed"));
		return false;
	}
	int32 newLeaderIndex = (leaderIndex - 1) % PlayableCharacters.Num();
	Leader = PlayableCharacters[newLeaderIndex];
	return true;
}
