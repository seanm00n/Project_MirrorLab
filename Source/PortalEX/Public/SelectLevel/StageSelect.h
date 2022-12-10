// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionBase.h"
#include "PortalEXGameInstance.h"
#include "StageSelect.generated.h"

UCLASS()
class PORTALEX_API AStageSelect : public AInteractionBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStageSelect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
		void Interaction(AActor* Projectile);
	virtual void Interaction_Implementation(AActor* Projectile) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Select|Parameter")
		FStageData mStageData;
};
