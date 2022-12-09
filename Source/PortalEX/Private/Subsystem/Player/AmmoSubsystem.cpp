// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/Player/AmmoSubsystem.h"

bool UAmmoSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return true;
}

void UAmmoSubsystem::SetAmmo(int32 newAmmo)
{
	CurrentStageAmmo = newAmmo;
}

int32 UAmmoSubsystem::GetAmmo() const
{
	return CurrentStageAmmo;
}
