// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/Stage/PortalEXPlayerStateBase.h"
#include "Subsystem/Player/AmmoSubsystem.h"

APortalEXPlayerStateBase::APortalEXPlayerStateBase()
	:mAmmo(3)
{
}

void APortalEXPlayerStateBase::BeginPlay()
{
	auto subsystem = UGameInstance::GetSubsystem<UAmmoSubsystem>(GetGameInstance());
	if (subsystem) {
		mAmmo = subsystem->GetAmmo();
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
