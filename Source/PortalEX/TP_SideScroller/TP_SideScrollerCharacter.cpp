// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_SideScrollerCharacter.h"
#include "PortalEX/PortalEXProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameMode/Stage/PortalEXPlayerStateBase.h"
#include "GameMode/Stage/PortalEXGameStateBase.h"
#include <Subsystem/World/WorldSubsystem_Stage.h>


ATP_SideScrollerCharacter::ATP_SideScrollerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;
	GetCharacterMovement()->RotationRate = FRotator(-1.0f, -1.0f, -1.0f);

	Pos_Gun = CreateDefaultSubobject<USceneComponent>(TEXT("POSGUN"));
	Pos_Gun->SetupAttachment(RootComponent);
	Pos_Gun->SetRelativeLocation(FVector(33.0f, 5.0f, -9.0f));

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MUZZLEPOSITION"));
	MuzzleLocation->SetupAttachment(Pos_Gun);
	MuzzleLocation->SetRelativeLocation(FVector(7.0f, 0.0f, 7.0f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATP_SideScrollerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);


	// Bind fire event
	PlayerInputComponent->BindAction("LeftFire", IE_Pressed, this, &ATP_SideScrollerCharacter::OnFire);

	PlayerInputComponent->BindAxis("MoveRight", this, &ATP_SideScrollerCharacter::MoveRight);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ATP_SideScrollerCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ATP_SideScrollerCharacter::TouchStopped);
}


void ATP_SideScrollerCharacter::Interaction_Implementation(AActor* Projectile)
{
	UE_LOG(LogTemp, Warning, TEXT("character Interact"))
		if (Cast<APortalEXProjectile>(Projectile)) {
			Projectile->Destroy();
		}
	GetCharacterMovement()->Launch(FVector(0, 0, GetCharacterMovement()->JumpZVelocity));

}

void ATP_SideScrollerCharacter::BeginPlay()
{
	Super::BeginPlay();

	auto GameState = Cast<APortalEXGameStateBase>(GetWorld()->GetGameState());
	if (GameState) {
		UE_LOG(LogTemp, Warning, TEXT("GameState,Start"));
		GameState->Start();
	}

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	//FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	//// Show or hide the two versions of the gun based on whether or not we're using motion controllers.
	//if (bUsingMotionControllers)
	//{
	//	VR_Gun->SetHiddenInGame(false, true);
	//	Mesh1P->SetHiddenInGame(true, true);
	//}
	//else
	//{
	//	VR_Gun->SetHiddenInGame(true, true);
	//	Mesh1P->SetHiddenInGame(false, true);
	//}
}

void ATP_SideScrollerCharacter::OnFire()
{
	// try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{

			float Direction = Dot3(
				GetActorRightVector(),
				GetActorRotation().Vector() * -1);
			FRotator rotation;
			if (Direction > 0) {
				rotation = FRotator(0, 90, 0);
			}
			else {
				rotation = FRotator(0, -90, 0);
			}

			const FRotator SpawnRotation = rotation;
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = ((MuzzleLocation != nullptr) ? MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			UE_LOG(LogTemp, Warning, TEXT("spawnProjectile"));
			auto playerState = Cast<APortalEXPlayerStateBase>(GetPlayerState());
			if (playerState) {
				if (playerState->GetAmmo() > 0) {
					// spawn the projectile at the muzzle
					auto projectile = World->SpawnActor<APortalEXProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
					if (projectile) {
						playerState->UseAmmo();
					}
				}

			}
			else {
				auto projectile = World->SpawnActor<APortalEXProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);


			}
		}
	}

	// try and play the sound if specified
	if (FireSound != nullptr)
	{
	
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	
}
void ATP_SideScrollerCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,1.0f,0.f), Value);
}

void ATP_SideScrollerCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void ATP_SideScrollerCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

