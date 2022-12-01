// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionBase.h"
#include "BindObj.generated.h"

UCLASS()
class PORTALEX_API ABindObj : public AInteractionBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABindObj();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void Interaction(AActor* Projectile);
	virtual void Interaction_Implementation(AActor* Projectile) override;

	
	UFUNCTION()
		void CharacterOverlap(AActor* MyOverlappedActor, AActor* OtherActor);
	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* Mesh;

	AActor* BindingProjectileActor;
};
