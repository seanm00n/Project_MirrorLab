// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

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
UCLASS()
class PORTALEX_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	//»ý¼ºÀÚ
};
