// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/VerticalObj.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AVerticalObj::AVerticalObj()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh->SetSimulatePhysics(true);
	Mesh->SetConstraintMode(EDOFMode::SixDOF);
	Mesh->GetBodyInstance()->bLockXRotation = true;
	Mesh->GetBodyInstance()->bLockYRotation = true;
	Mesh->GetBodyInstance()->bLockZRotation = true;
	Mesh->GetBodyInstance()->bLockXTranslation = true;
	Mesh->GetBodyInstance()->bLockYTranslation = true;


	Mesh->OnComponentHit.AddDynamic(this, &AVerticalObj::Hit);
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
	
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	//MoveComponentTo 종료 후 콜백함수 지정
	LatentInfo.ExecutionFunction = FName();
	LatentInfo.Linkage = 0;
	LatentInfo.UUID = 0;

	UKismetSystemLibrary::MoveComponentTo(Mesh, GetActorLocation() + FVector(0, 0, JumpLocation), GetActorRotation(), false, false, 0.2, false, EMoveComponentAction::Type::Move, LatentInfo);

	UE_LOG(LogTemp, Warning, TEXT("Vertical implement "));
}

void AVerticalObj::Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//UKismetSystemLibrary::BoxTraceSingle(GetOwner()->GetWorld(),)
}



