// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/Stage/PortalEXGameStateBase.h"
#include "Blueprint/UserWidget.h"
#include <PortalEXGameInstance.h>
#include <Subsystem/World/WorldSubsystem_Stage.h>
#include "Kismet/GameplayStatics.h"
#include <PortalEX/Public/Subsystem/World/PortalEXWorldSettings.h>

APortalEXGameStateBase::APortalEXGameStateBase()
	:mStageState(EStageState::Start)
{
}

void APortalEXGameStateBase::Start()
{
	//점수 init, 타이머 init, 
	auto WorldSetting = Cast<APortalEXWorldSettings>(GetWorld()->GetWorldSettings());
	if (WorldSetting) {
		UE_LOG(LogTemp, Warning, TEXT("ShouldCreateSubsystem WorldSubSystem success"));
		if (WorldSetting->bCurrentStage) {
			auto WorldSubSystem = GetWorld()->GetSubsystem<UWorldSubsystem_Stage>();
			WorldSubSystem->SetTimer();
			WorldSubSystem->SetScore(0);
			CurrentLevelName = FName((GetWorld()->GetCurrentLevel()->GetName()));
		}
	}
}

void APortalEXGameStateBase::Playing()
{
	//정지 UI 해제, 다시 플레이 

	SetGamePaused(false);
}

void APortalEXGameStateBase::Pause()
{
	//게임 정지, 정지 UI
	
	SetGamePaused(true);

	/*auto PauseWidget = CreateWidget<UUserWidget>(GetGameInstance(), WidgetClass);
	if (PauseWidget) {
		PauseWidget->AddToViewport();
	}*/
}

void APortalEXGameStateBase::Restart()
{
	// stage load or PlayState init, stage Stage 호출
	// 
	// 현재 레벨 이름은 디테일에서 편집
	if (CurrentLevelName != "")
	{
		UE_LOG(LogTemp, Warning, TEXT("APortalEXGameStateBase::Restart"));
		UGameplayStatics::OpenLevel(this, CurrentLevelName);
	}

}

void APortalEXGameStateBase::Clear()
{
	//점수 save,클리어 데이터 save, clear UI
	auto GameInstance = Cast<UPortalEXGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance) {
		auto StageData = GameInstance->GetCurrentStageData();

		auto WorldSubSystem = GetWorld()->GetSubsystem<UWorldSubsystem_Stage>();
		auto clearHUD = CreateWidget<UUserWidget>(GetGameInstance(), ClearWidgetClass);
		StageData.Score += 35 * WorldSubSystem->GetTime();
		WorldSubSystem->SetScore(StageData.Score);
		StageData.isClear = true;
		if (clearHUD) {
			clearHUD->AddToViewport();
		}
		Pause();
		GameInstance->Save(StageData);
		auto Controller = GetWorld()->GetFirstPlayerController();
		if (Controller) {
			Controller->SetShowMouseCursor(true);
		}
		mStageState = EStageState::Clear;
	}
}

FName APortalEXGameStateBase::GetCurrentLevelName() const
{
	return CurrentLevelName;
}

void APortalEXGameStateBase::SetCurrentLevelName(FName levelName)
{
	
	CurrentLevelName = levelName;
}

void APortalEXGameStateBase::SetGamePaused(bool bIsPaused)
{
	APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	if (MyPlayer != NULL)
	{
		MyPlayer->SetPause(bIsPaused);
	}
}

EStageState APortalEXGameStateBase::GetState() const
{
	return mStageState;
}
