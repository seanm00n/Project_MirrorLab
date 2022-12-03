// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionBase.h"

// Sets default values
AInteractionBase::AInteractionBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Mesh;

}

// Called when the game starts or when spawned
void AInteractionBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractionBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

