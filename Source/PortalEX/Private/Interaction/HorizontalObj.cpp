// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/HorizontalObj.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AHorizontalObj::AHorizontalObj()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh->SetSimulatePhysics(true);
	Mesh->SetConstraintMode(EDOFMode::SixDOF);
	Mesh->GetBodyInstance()->bLockXRotation = true;
	Mesh->GetBodyInstance()->bLockYRotation = true;
	Mesh->GetBodyInstance()->bLockZRotation = true;
	Mesh->GetBodyInstance()->bLockXTranslation = true;

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
	/*static void MoveComponentTo
	(
		USceneComponent * Component,
		FVector TargetRelativeLocation,
		FRotator TargetRelativeRotation,
		bool bEaseOut,
		bool bEaseIn,
		float OverTime,
		bool bForceShortestRotationPath,
		TEnumAsByte< EMoveComponentAction::Type > MoveAction,
		FLatentActionInfo LatentInfo
	)*/
	float Direction = 0;
	auto dirVec = Projectile->GetActorLocation() - GetActorLocation();
	dirVec.Normalize();
	if (Projectile) {
		Direction = Dot3(GetActorRightVector(), dirVec);

		UE_LOG(LogTemp, Warning, TEXT("Horizontal implement %f"), Direction);
	}


	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	//MoveComponentTo 종료 후 콜백함수 지정
	LatentInfo.ExecutionFunction = FName("MoveToTargetFinished");
	LatentInfo.Linkage = 0;
	LatentInfo.UUID = 0;
	
	if (Direction >=0) {

		UKismetSystemLibrary::MoveComponentTo(Mesh, GetActorLocation() + FVector(0, -100, 0), GetActorRotation(), false, false, 0.2, false, EMoveComponentAction::Type::Move, LatentInfo);

		UE_LOG(LogTemp, Warning, TEXT("Horizontal implement 1"));
	}
	else {
		UKismetSystemLibrary::MoveComponentTo(Mesh, GetActorLocation() + FVector(0, 100, 0), GetActorRotation(), false, false, 0.2, false, EMoveComponentAction::Type::Move, LatentInfo);

		UE_LOG(LogTemp, Warning, TEXT("Horizontal implement -1"));
	}
	UE_LOG(LogTemp, Warning, TEXT("Horizontal implement OK"));
}




