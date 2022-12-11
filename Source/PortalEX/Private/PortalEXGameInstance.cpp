// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalEXGameInstance.h"
#include "PortalEXSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include <PortalEX/Public/Subsystem/World/PortalEXWorldSettings.h>


void UPortalEXGameInstance::SetTime(float newTime)
{
	mStageData.StageTime = newTime;
}

float UPortalEXGameInstance::GetTime() const
{
	return mStageData.StageTime;
}

void UPortalEXGameInstance::SetAmmo(int32 newAmmo)
{
	mStageData.StageAmmo = newAmmo;
}

int32 UPortalEXGameInstance::GetAmmo() const
{
	return mStageData.StageAmmo;
}

FStageData UPortalEXGameInstance::GetCurrentStageData() const
{
	return mStageData;
}

void UPortalEXGameInstance::isStage()
{
	auto WorldSetting = Cast<APortalEXWorldSettings>(GetWorld()->GetWorldSettings());
	if (WorldSetting) {
		WorldSetting->bCurrentStage = true;
	}

}

void UPortalEXGameInstance::isNotStage()
{
	auto WorldSetting = Cast<APortalEXWorldSettings>(GetWorld()->GetWorldSettings());
	if (WorldSetting) {
		WorldSetting->bCurrentStage = false;
	}
}

void UPortalEXGameInstance::Save(const FStageData& StageData)
{
	UPortalEXSaveGame* saveData = Cast<UPortalEXSaveGame>(UGameplayStatics::CreateSaveGameObject(UPortalEXSaveGame::StaticClass()));
	saveData->SaveStageDate = StageData;
	UGameplayStatics::SaveGameToSlot(saveData, saveData->SaveStageDate.LevelName, saveData->SaveStageDate.SlotIndex);

	UE_LOG(LogTemp, Warning, TEXT("saving"));
}

FStageData UPortalEXGameInstance::Load(const FStageData& StageData)
{
	UPortalEXSaveGame* loadData = Cast<UPortalEXSaveGame>(UGameplayStatics::CreateSaveGameObject(UPortalEXSaveGame::StaticClass()));

	UE_LOG(LogTemp, Warning, TEXT("loading"));

	loadData = Cast<UPortalEXSaveGame>(UGameplayStatics::LoadGameFromSlot(StageData.LevelName, StageData.SlotIndex));
	if (loadData) {
		mStageData = loadData->SaveStageDate;
	}
	
	return mStageData;
}
