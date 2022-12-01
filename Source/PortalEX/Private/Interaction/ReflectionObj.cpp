// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/ReflectionObj.h"

// Sets default values
AReflectionObj::AReflectionObj()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AReflectionObj::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AReflectionObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AReflectionObj::Interaction_Implementation(AActor* Projectile)
{
}

