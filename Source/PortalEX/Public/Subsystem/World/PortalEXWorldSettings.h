// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "PortalEXWorldSettings.generated.h"

/**
 * 
 */
UCLASS()
class PORTALEX_API APortalEXWorldSettings : public AWorldSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		bool bCurrentStage = false;

};