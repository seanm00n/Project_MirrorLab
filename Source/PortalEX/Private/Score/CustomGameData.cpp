// Fill out your copyright notice in the Description page of Project Settings.


#include "Score/CustomGameData.h"

UCustomGameData::UCustomGameData()
{
	stageNum = StageNum::None;
}

StageNum UCustomGameData::GetStageNum()
{
	return stageNum;
}
void UCustomGameData::Init()
{
	Super::Init();
}
UCustomGameData* UCustomGameData::GetInstance() {
	if (gameData == NULL) {
		gameData = NewObject<UCustomGameData>();
	}
	return gameData;
}