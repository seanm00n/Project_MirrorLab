// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectLevel/StageSelect.h"

// Sets default values
AStageSelect::AStageSelect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStageSelect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStageSelect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStageSelect::Interaction_Implementation(AActor* Projectile)
{
}

