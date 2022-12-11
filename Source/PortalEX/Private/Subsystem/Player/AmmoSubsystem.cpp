// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/Player/AmmoSubsystem.h"
#include <PortalEX/Public/Subsystem/World/PortalEXWorldSettings.h>
#include <PortalEXGameInstance.h>

bool UAmmoSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    if (!Super::ShouldCreateSubsystem(Outer))
    {
        return false;
    }

    if (UWorld* WorldOuter = Cast<UWorld>(Outer))
    {
        auto WorldSetting = Cast<APortalEXWorldSettings>(WorldOuter->GetWorldSettings());
        if (WorldSetting) {
            UE_LOG(LogTemp, Warning, TEXT("ShouldCreateSubsystem AmmoSubsystem success"));
            return WorldSetting->bCurrentStage;
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("ShouldCreateSubsystem AmmoSubsystem fail"));
    return false;
}

void UAmmoSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    auto gameInstance = Cast<UPortalEXGameInstance>(GetWorld()->GetGameInstance());
    if (!gameInstance) {
        UE_LOG(LogTemp, Warning, TEXT("GameInstance cast fail"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("GameInstance cast success"));
    auto StageData = gameInstance->Load(gameInstance->GetCurrentStageData());

    CurrentStageAmmo = StageData.StageAmmo;
    UE_LOG(LogTemp, Warning, TEXT("CurrentStageAmmo : %d"), CurrentStageAmmo);
}

void UAmmoSubsystem::SetAmmo(int32 newAmmo)
{
	CurrentStageAmmo = newAmmo;
}

int32 UAmmoSubsystem::GetAmmo() const
{
	return CurrentStageAmmo;
}
