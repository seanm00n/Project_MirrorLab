// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/SwitchObj.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ASwitchObj::ASwitchObj()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASwitchObj::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASwitchObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASwitchObj::Interaction_Implementation(AActor* Projectile)
{
	Projectile->Destroy();
	if (DoorRef) {
		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this;
		//MoveComponentTo 종료 후 콜백함수 지정
		LatentInfo.ExecutionFunction = FName();
		LatentInfo.Linkage = 0;
		LatentInfo.UUID = 0;

		switch (OpenType)
		{
		case EOpenDir::Right:
			UKismetSystemLibrary::MoveComponentTo(DoorRef->GetRootComponent(), DoorRef->GetActorLocation() + FVector(0, -OpenRightDistance, 0), GetActorRotation(), false, false, 0.2, false, EMoveComponentAction::Type::Move, LatentInfo);

			break;
		case EOpenDir::Left:
			UKismetSystemLibrary::MoveComponentTo(DoorRef->GetRootComponent(), DoorRef->GetActorLocation() + FVector(0, OpenLeftDistance, 0), GetActorRotation(), false, false, 0.2, false, EMoveComponentAction::Type::Move, LatentInfo);

			break;
		case EOpenDir::Up:
			UKismetSystemLibrary::MoveComponentTo(DoorRef->GetRootComponent(), DoorRef->GetActorLocation() + FVector(0, 0, OpenUpDistance), GetActorRotation(), false, false, 0.2, false, EMoveComponentAction::Type::Move, LatentInfo);

			break;
		case EOpenDir::Down:
			UKismetSystemLibrary::MoveComponentTo(DoorRef->GetRootComponent(), DoorRef->GetActorLocation() + FVector(0, 0, -OpenDownDistance), GetActorRotation(), false, false, 0.2, false, EMoveComponentAction::Type::Move, LatentInfo);

			break;
		default:
			break;
		}
	}
}

