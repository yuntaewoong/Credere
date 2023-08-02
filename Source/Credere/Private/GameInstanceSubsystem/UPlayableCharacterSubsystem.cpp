// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstanceSubsystem/UPlayableCharacterSubsystem.h"
#include "Character\ABaseCharacter.h"
#include "Controller\AHumanPlayerController.h"
#include "Controller\APartnerAIController.h"


DEFINE_LOG_CATEGORY(LogGameInstance);

UPlayableCharacterSubsystem::UPlayableCharacterSubsystem()
	:
	Super::UGameInstanceSubsystem(),
	PlayableCharacters(TArray<ABaseCharacter*>()),
	Leader(nullptr)
{
	PlayableCharacters.Reserve(MAX_PLAYER_NUM);
}

void UPlayableCharacterSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

}

void UPlayableCharacterSubsystem::Deinitialize()
{
}

void UPlayableCharacterSubsystem::AddPlayer(ABaseCharacter& Player)
{
	PlayableCharacters.Add(&Player);
}

void UPlayableCharacterSubsystem::SetLeader(ABaseCharacter& Player)
{
	Leader = &Player;
}

const ABaseCharacter& UPlayableCharacterSubsystem::GetLeader() const
{
	return *Leader;
}

bool UPlayableCharacterSubsystem::IsLeader(const ABaseCharacter& Player) const
{
	return Leader == &Player;
}

bool UPlayableCharacterSubsystem::ChangeCharacterForward()
{//정방향으로 리더전환 ex/ 1 , 2(리더), 3 -> 1,2,3(리더)
	if(!Leader)
	{
		UE_LOG(LogGameInstance,Error,TEXT("Leader Is Not Setted"));
		return false;
	}
	TArray<AController*> currentControllers;
	currentControllers.Reserve(PlayableCharacters.Num());
	for(int32 i = 0;i<PlayableCharacters.Num();i++)
	{//컨트롤러 배열 생성
		currentControllers.Add(
			CastChecked<AController>(PlayableCharacters[i]->GetOwner())
		);
	}
	for(int32 i = 0;i<currentControllers.Num();i++)
	{//모든 컨트롤러가 현재 캐릭터를 Unpossess하고 다음 캐릭터를 Possess
		int32 nextPlayerIndex = (i + 1) % PlayableCharacters.Num();
		currentControllers[i]->Possess(PlayableCharacters[nextPlayerIndex]);
		if(AHumanPlayerController* leaderController = Cast<AHumanPlayerController>(currentControllers[i]))
		{//리더 컨트롤러일시 리더 변경
			Leader = PlayableCharacters[nextPlayerIndex];
		}
	}
	return true;
}

bool UPlayableCharacterSubsystem::ChangeCharacterBackward()
{//역방향으로 리더전환 ex/ 1, 2(리더),3->1(리더),2,3
	if(!Leader)
	{
		UE_LOG(LogGameInstance,Error,TEXT("Leader Is Not Setted"));
		return false;
	}
	TArray<AController*> currentControllers;
	currentControllers.Reserve(PlayableCharacters.Num());
	for(int32 i = 0;i<PlayableCharacters.Num();i++)
	{//컨트롤러 배열 생성
		currentControllers.Add(
			CastChecked<AController>(PlayableCharacters[i]->GetOwner())
		);
	}
	for(int32 i = 0;i<currentControllers.Num();i++)
	{//모든 컨트롤러가 현재 캐릭터를 Unpossess하고 이전 캐릭터를 Possess
		int32 nextPlayerIndex = (i + PlayableCharacters.Num() - 1) % PlayableCharacters.Num();
		currentControllers[i]->Possess(PlayableCharacters[nextPlayerIndex]);
		if(AHumanPlayerController* leaderController = Cast<AHumanPlayerController>(currentControllers[i]))
		{//리더 컨트롤러일시 리더 변경
			Leader = PlayableCharacters[nextPlayerIndex];
		}
	}
	return true;
}
