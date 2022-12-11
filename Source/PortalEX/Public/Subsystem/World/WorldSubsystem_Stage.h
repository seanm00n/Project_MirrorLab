// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "WorldSubsystem_Stage.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTimerSignature);
/**
 * 
 */

UCLASS()
class PORTALEX_API UWorldSubsystem_Stage : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, Category = "Collision")
	FTimerSignature TimerDelegate;
public:


	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	UFUNCTION(BlueprintCallable, Category = "WorldSub|Time")
		float GetTime()const;

	UFUNCTION(BlueprintCallable, Category = "WorldSub|Score")
		void SetScore(int32 newScore);
	UFUNCTION(BlueprintCallable, Category = "WorldSub|Score")
		int32 GetScore() const;

	UFUNCTION(BlueprintCallable, Category = "WorldSub|Ammo")
		void SetAmmo(int32 newAmmo);
	UFUNCTION(BlueprintCallable, Category = "WorldSub|Ammo")
		int32 GetAmmo() const;

	UFUNCTION(BlueprintCallable, Category = "WorldSub|Level")
	void SetLevelName(FString newName);
	UFUNCTION(BlueprintCallable, Category = "WorldSub|Level")
	FString GetLevelName() const;

	

	UFUNCTION()
		void SetTimer();
	UFUNCTION()
	void ClearTimer();
	UFUNCTION()
		void TimeCount();

	UFUNCTION(BlueprintCallable, Category = "GameInstance|Function")
	FTimerHandle GetTimerHandle() const;
	UFUNCTION()
		void Init();
protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
private:
	UPROPERTY(VisibleAnywhere, Category = "Parameter|Ammo", meta = (AllowPrivateAccess = "true"))
		int32 CurrentStageAmmo;

	UPROPERTY(VisibleAnywhere, Category = "Parameter|Score", meta = (AllowPrivateAccess = "true"))
		int32 CurrentStageScore;

	UPROPERTY(VisibleAnywhere, Category = "Parameter|Time", meta = (PrivateAccessAllow = "true"))
	int32 CurrentStageTime;

	UPROPERTY(VisibleAnywhere, Category = "Parameter|Level", meta = (PrivateAccessAllow = "true"))
	FString CurrentStageLevelName;

	UPROPERTY(VisibleAnywhere, Category = "Parameter|Time", meta = (AllowPrivateAccess = "true"))
		FTimerHandle StageTimerHandle;

};
