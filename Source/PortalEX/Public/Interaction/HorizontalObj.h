// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionBase.h"
#include "HorizontalObj.generated.h"

UCLASS()
class PORTALEX_API AHorizontalObj : public AInteractionBase
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, Category = "Paramter", meta = (PrivateAccessAllow = "true"))
		float mDistance;
public:	
	// Sets default values for this actor's properties
	AHorizontalObj();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Interact|Trace")
		bool isMovable(float dir,float distance);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
		void Interaction(AActor* Projectile);
	virtual void Interaction_Implementation(AActor* Projectile) override;

	

};
