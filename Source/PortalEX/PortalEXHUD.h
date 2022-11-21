// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PortalEXHUD.generated.h"

UCLASS()
class APortalEXHUD : public AHUD
{
	GENERATED_BODY()

public:
	APortalEXHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

