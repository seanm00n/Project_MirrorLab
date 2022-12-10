// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/Stage/PortalEXPlayerStateBase.h"
#include "Subsystem/Player/AmmoSubsystem.h"
#include<Subsystem/World/WorldSubsystem_Stage.h>

APortalEXPlayerStateBase::APortalEXPlayerStateBase()
	:mAmmo(3)
{
}

void APortalEXPlayerStateBase::BeginPlay()
{
	//auto worldSubSystem = UGame
	auto MyWorldSubsystem = GetWorld()->GetSubsystem<UWorldSubsystem_Stage>();
	if (MyWorldSubsystem) {
		UE_LOG(LogTemp, Warning, TEXT("APortalEXPlayerStateBase init"));
		mAmmo = MyWorldSubsystem->GetAmmo();
	}
}

int32 APortalEXPlayerStateBase::GetAmmo() const
{
	return mAmmo;
}

void APortalEXPlayerStateBase::UseAmmo()
{
	mAmmo--;
}
