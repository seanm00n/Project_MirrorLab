// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/BindObj.h"
#include "PortalEX/PortalEXProjectile.h"
#include "PortalEX/TP_SideScroller/TP_SideScrollerCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABindObj::ABindObj()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	this->OnActorBeginOverlap.AddDynamic(this, &ABindObj::CharacterOverlap);
}

// Called when the game starts or when spawned
void ABindObj::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABindObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABindObj::Interaction_Implementation(AActor* Projectile)
{
	if (IsValid(BindingProjectileActor)) {
		return;
	}

	auto Target = Cast<APortalEXProjectile>(Projectile);
	if (Target) {
		auto movement = Target->GetProjectileMovement();
		movement->StopMovementImmediately();
		Target->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		Target->SetLifeSpan(0);

		BindingProjectileActor = Target;

		Mesh->SetCollisionProfileName(FName("Interact"));
		//Mesh->SetCollisionObjectType(ECollisionChannel::);
	}
}

void ABindObj::CharacterOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("BindObj Overlap"));
	if (BindingProjectileActor == nullptr)
		return;
	auto Character = Cast<ATP_SideScrollerCharacter>(OtherActor);

	UE_LOG(LogTemp, Warning, TEXT("BindObj Overlap"));
	if (Character) {
		if (Character->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass())) {
			auto Interact = Cast<IInteractionInterface>(Character);
			Interact->Interaction_Implementation(nullptr);

			BindingProjectileActor->Destroy();
			BindingProjectileActor = nullptr;

			Mesh->SetCollisionProfileName(FName("OverlapAllDynamic"));
		}
	}
}	


