// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/World/WorldSubsystem_Stage.h"
#include "Subsystem/World/PortalEXWorldSettings.h"
#include <PortalEXGameInstance.h>
#include <PortalEX/Public/GameMode/Stage/PortalEXGameStateBase.h>

bool UWorldSubsystem_Stage::ShouldCreateSubsystem(UObject* Outer) const
{
    if (!Super::ShouldCreateSubsystem(Outer))
    {
        return false;
    }

    if (UWorld* WorldOuter = Cast<UWorld>(Outer))
    {
        auto WorldSetting = Cast<APortalEXWorldSettings>(WorldOuter->GetWorldSettings());
        if (WorldSetting) {
            UE_LOG(LogTemp, Warning, TEXT("ShouldCreateSubsystem WorldSubSystem success"));
            return WorldSetting->bCurrentStage;
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("ShouldCreateSubsystem WorldSubSystem fail"));
    return false;
}

float UWorldSubsystem_Stage::GetTime() const
{
  
    return CurrentStageTime;
}

void UWorldSubsystem_Stage::SetScore(int32 newScore)
{
    CurrentStageScore = newScore;
}

int32 UWorldSubsystem_Stage::GetScore() const
{
    return CurrentStageScore;
}

void UWorldSubsystem_Stage::SetTimer()
{
    GetWorld()->GetTimerManager().SetTimer(StageTimerHandle, this, &UWorldSubsystem_Stage::TimeCount, 1.0f, true);
}

void UWorldSubsystem_Stage::TimeCount()
{
    UE_LOG(LogTemp, Warning, TEXT("CurrentStageTime , TimeCount : %f"), CurrentStageTime);
    if (CurrentStageTime <= 0) {

        GetWorld()->GetTimerManager().ClearTimer(StageTimerHandle);
        //Test 삭제예정
        auto gameState = Cast<APortalEXGameStateBase>(GetWorld()->GetGameState());
        gameState->Clear();
        return;
    }
    CurrentStageTime--;
}

FTimerHandle UWorldSubsystem_Stage::GetTimerHandle() const
{
    return StageTimerHandle;
}

void UWorldSubsystem_Stage::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    auto gameInstance = Cast<UPortalEXGameInstance>(GetWorld()->GetGameInstance());
    if (!gameInstance) {
        UE_LOG(LogTemp, Warning, TEXT("GameInstance cast fail"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("GameInstance cast success"));
    auto StageData = gameInstance->Load(gameInstance->GetCurrentStageData());

    CurrentStageTime = StageData.StageTime;
    UE_LOG(LogTemp, Warning, TEXT("Time : %f"), CurrentStageTime);
    CurrentStageAmmo = StageData.StageAmmo;
    UE_LOG(LogTemp, Warning, TEXT("CurrentStageAmmo : %d"), CurrentStageAmmo);
   

    //GetWorld()->GetTimerManager().SetTimer(StageCountDownTimerHandle, this, &UWorldSubsystem_Stage::TimeCount, 1.0f,true);
}

void UWorldSubsystem_Stage::SetAmmo(int32 newAmmo)
{
    CurrentStageAmmo = newAmmo;
}

int32 UWorldSubsystem_Stage::GetAmmo() const
{
    return CurrentStageAmmo;
}





