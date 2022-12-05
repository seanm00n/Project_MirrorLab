// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/Stage/PortalEXGameStateBase.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

APortalEXGameStateBase::APortalEXGameStateBase()
	:mStageState(EStageState::Start)
{
}

void APortalEXGameStateBase::Start()
{
	//점수 init, 타이머 init, 
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
