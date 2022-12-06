// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CustomGameData.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class StageNum : uint8 {
	One UMETA(DisplayName = "Stage One"), 
	Two UMETA(DisplayName = "Stage Two"), 
	Three UMETA(DisplayName = "Stage Three"), 
	None UMETA(DisplayName = "Stage None")
};
UCLASS(BlueprintType)
class PORTALEX_API UCustomGameData : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;

	UFUNCTION(BlueprintPure, Category="Custom")
	static UCustomGameData* GetInstance();

	UFUNCTION(BlueprintPure, Category="Custom")
	StageNum GetStageNum();

private:
	UCustomGameData();//private?
	static UCustomGameData* gameData;
	StageNum stageNum;
};
