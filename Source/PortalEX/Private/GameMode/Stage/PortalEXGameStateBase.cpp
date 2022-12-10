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
	//���� init, Ÿ�̸� init, 
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
	//���� UI ����, �ٽ� �÷��� 

	SetGamePaused(false);
}

void APortalEXGameStateBase::Pause()
{
	//���� ����, ���� UI
	
	SetGamePaused(true);

	/*auto PauseWidget = CreateWidget<UUserWidget>(GetGameInstance(), WidgetClass);
	if (PauseWidget) {
		PauseWidget->AddToViewport();
	}*/
}

void APortalEXGameStateBase::Restart()
{
	// stage load or PlayState init, stage Stage ȣ��
	// 
	// ���� ���� �̸��� �����Ͽ��� ����
	if (CurrentLevelName != "")
	{
		UE_LOG(LogTemp, Warning, TEXT("APortalEXGameStateBase::Restart"));
		UGameplayStatics::OpenLevel(this, CurrentLevelName);
	}

}

void APortalEXGameStateBase::Clear()
{
	//���� save,Ŭ���� ������ save, clear UI
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
