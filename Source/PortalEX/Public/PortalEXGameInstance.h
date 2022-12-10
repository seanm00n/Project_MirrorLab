// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PortalEXGameInstance.generated.h"


USTRUCT(Atomic, BlueprintType)
struct FStageData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageData")
		FString LevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageData")
		int32 SlotIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageData")
		float StageTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageData")
		int32 StageAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageData")
		int32 Score;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageData")
		bool isClear;

};
/**
 * 
 */
UCLASS()
class PORTALEX_API UPortalEXGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable, Category = "GameInstance|Function")
		void SetTime(float newTime);

	UFUNCTION(BlueprintCallable, Category = "GameInstance|Function")
		float GetTime() const;

	UFUNCTION(BlueprintCallable, Category = "GameInstance|Function")
		void SetAmmo(int32 newAmmo);

	UFUNCTION(BlueprintCallable, Category = "GameInstance|Function")
		int32 GetAmmo() const;
	UFUNCTION(BlueprintCallable, Category = "GameInstance|Function")
		FStageData GetCurrentStageData() const;

public:

	UFUNCTION(BlueprintCallable, Category = "GameInstance|Function")
		void Save(const FStageData& StageData);
	UFUNCTION(BlueprintCallable, Category = "GameInstance|Function")
		FStageData Load(const FStageData& StageData);

private:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameInstance|Parameter", meta = (AllowPrivateAccess = "true"))
		FStageData mStageData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameInstance|Parameter", meta = (AllowPrivateAccess = "true"))
		TArray<FStageData> mStageDatas;

};
