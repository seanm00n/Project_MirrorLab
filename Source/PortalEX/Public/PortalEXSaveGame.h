// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PortalEXGameInstance.h"
#include "PortalEXSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PORTALEX_API UPortalEXSaveGame : public USaveGame
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save|Data")
		FStageData SaveStageDate;
public:
	UPortalEXSaveGame();
};
