// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/VerticalObj.h"

// Sets default values
AVerticalObj::AVerticalObj()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVerticalObj::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVerticalObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVerticalObj::Interaction_Implementation(AActor* Projectile)
{
}

