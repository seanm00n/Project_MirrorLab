// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionBase.h"
#include "SwitchObj.generated.h"
UENUM(BlueprintType)
enum class EOpenDir : uint8
{
	Right,
	Left,
	Up,
	Down
};
UCLASS()
class PORTALEX_API ASwitchObj : public AInteractionBase
{
	GENERATED_BODY()
	
	

public:	
	
	// Sets default values for this actor's properties
	ASwitchObj();
	


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameter")
		AActor* DoorRef;

	UPROPERTY(EditAnywhere, Category = "Parameter")
		EOpenDir  OpenType = EOpenDir::Right;
	
	UPROPERTY(EditAnywhere, Category = "Parameter", meta = (EditCondition = "OpenType == EOpenDir::Right", EditConditionHides))
		float	OpenRightDistance = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Parameter", meta = (EditCondition = "OpenType == EOpenDir::Left", EditConditionHides))
		float	OpenLeftDistance = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Parameter", meta = (EditCondition = "OpenType == EOpenDir::Up", EditConditionHides))
		float	OpenUpDistance = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Parameter", meta = (EditCondition = "OpenType == EOpenDir::Down", EditConditionHides))
		float	OpenDownDistance = 100.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
		void Interaction(AActor* Projectile);
	virtual void Interaction_Implementation(AActor* Projectile) override;

};
