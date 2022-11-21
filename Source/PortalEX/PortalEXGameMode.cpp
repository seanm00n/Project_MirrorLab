// Copyright Epic Games, Inc. All Rights Reserved.

#include "PortalEXGameMode.h"
#include "PortalEXHUD.h"
#include "PortalEXCharacter.h"
#include "UObject/ConstructorHelpers.h"

APortalEXGameMode::APortalEXGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = APortalEXHUD::StaticClass();
}
