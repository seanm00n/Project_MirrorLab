// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PortalEXGameStateBase.generated.h"

/**
 * 
 */
UENUM()
enum class EStageState: uint8
{
	Start,
	Playing,
	Pause,
	Restart,
	Clear
};

UCLASS()
class PORTALEX_API APortalEXGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	APortalEXGameStateBase();

	UFUNCTION(BlueprintCallable,Category="GameState|Execute")
		virtual void Start();
	UFUNCTION(BlueprintCallable, Category = "GameState|Execute")
		virtual void Playing();
	UFUNCTION(BlueprintCallable, Category = "GameState|Execute")
		virtual void Pause();
	UFUNCTION(BlueprintCallable, Category = "GameState|Execute")
		virtual void Restart();
	UFUNCTION(BlueprintCallable, Category = "GameState|Execute")
		virtual void Clear();

	UFUNCTION(BlueprintCallable, Category = "GameState|Function")
	EStageState GetState() const;


	UFUNCTION(BlueprintCallable, Category = "GameState|Function")
		FName GetCurrentLevelName()const;
	UFUNCTION(BlueprintCallable, Category = "GameState|Function")
		void SetCurrentLevelName(FName levelName);
protected:
	void SetGamePaused(bool bIsPaused);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Parameter", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> ClearWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameter", meta = (AllowPrivateAccess = "true"))
		FName CurrentLevelName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameter", meta = (AllowPrivateAccess = "true"))
		FName StageSelectLevelName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameter", meta = (AllowPrivateAccess = "true"))
		FName MainLevelName;

	EStageState mStageState;
};
