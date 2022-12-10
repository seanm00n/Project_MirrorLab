// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmmoSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class PORTALEX_API UAmmoSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:

	virtual bool ShouldCreateSubsystem(UObject* Outer) const;

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection);
	
	UFUNCTION(BlueprintCallable, Category = "SubSystem")
		void SetAmmo(int32 newAmmo);
	UFUNCTION(BlueprintCallable, Category = "SubSystem")
		int32 GetAmmo() const;
	
	UPROPERTY(VisibleAnywhere)
		int32 CurrentStageAmmo;

};
