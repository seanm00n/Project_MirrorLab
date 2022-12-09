// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/MirrorObj.h"

// Sets default values
AMirrorObj::AMirrorObj()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMirrorObj::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMirrorObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMirrorObj::Interaction_Implementation(AActor* Projectile)
{
}

