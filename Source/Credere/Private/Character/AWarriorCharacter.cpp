// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AWarriorCharacter.h"

AWarriorCharacter::AWarriorCharacter()
	: Super::ABaseCharacter()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/Characters/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));
	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	else
		UE_LOG(LogSkeletalMesh, Error, TEXT("Warrior Skeletal Mesh Not Loaded"));
	GetMesh()->AddRelativeLocation(FVector(0.0, 0.0, SkeletalMeshAdjust));
}
