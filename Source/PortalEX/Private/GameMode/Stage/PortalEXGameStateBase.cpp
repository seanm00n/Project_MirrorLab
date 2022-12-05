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
	//���� init, Ÿ�̸� init, 
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
