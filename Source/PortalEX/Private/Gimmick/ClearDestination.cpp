// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/ClearDestination.h"
#include <PortalEX/TP_SideScroller/TP_SideScrollerCharacter.h>
#include <PortalEX/Public/GameMode/Stage/PortalEXGameStateBase.h>

// Sets default values
AClearDestination::AClearDestination()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	RootComponent = Mesh;
	OnActorHit.AddDynamic(this, &AClearDestination::ActorHit);
}

void AClearDestination::ActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	auto Character = Cast<ATP_SideScrollerCharacter>(OtherActor);
	if (Character) {
		UE_LOG(LogTemp, Warning, TEXT("Cast ClearDest Character success"));
		auto GameState = Cast<APortalEXGameStateBase>(GetWorld()->GetGameState());
		if (GameState) {
			GameState->Clear();
		}
	}
}

// Called when the game starts or when spawned
void AClearDestination::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AClearDestination::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

