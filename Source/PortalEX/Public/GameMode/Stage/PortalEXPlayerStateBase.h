// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PortalEXPlayerStateBase.generated.h"

/**
 * 
 */
UCLASS()
class PORTALEX_API APortalEXPlayerStateBase : public APlayerState
{
	GENERATED_BODY()
public:
	APortalEXPlayerStateBase();

	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
		int32 GetAmmo() const;
	UFUNCTION(BlueprintCallable)
		void UseAmmo();
private:
	UPROPERTY(VisibleAnywhere, Category = "Stat")
		int32 mAmmo;
};
