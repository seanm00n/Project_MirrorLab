// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/HorizontalObj.h"

// Sets default values
AHorizontalObj::AHorizontalObj()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHorizontalObj::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHorizontalObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHorizontalObj::Interaction_Implementation(AActor* Projectile)
{
}

