// Copyright Epic Games, Inc. All Rights Reserved.

#include "PortalEXProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "InteractionInterface.h"
#include "Components/SphereComponent.h"

APortalEXProjectile::APortalEXProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &APortalEXProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void APortalEXProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Projectile Hit"));
	if (OtherActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass())) {

		UE_LOG(LogTemp, Warning, TEXT("ImplementsInterface"));
		auto Interfact = Cast<IInteractionInterface>(OtherActor);
		if (Interfact) {

			UE_LOG(LogTemp, Warning, TEXT("Interfact"));
			Interfact->Execute_Interaction(OtherActor, this);
		}
	}
	else if (Cast<APortalEXProjectile>(OtherActor)) {

	}
	else {
		Destroy();
	}
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{

		//OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		Destroy();
	}
}