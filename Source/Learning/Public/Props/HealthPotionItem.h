// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Props/PickUpItemBase.h"
#include "HealthPotionItem.generated.h"

/**
 * 
 */
UCLASS()
class LEARNING_API AHealthPotionItem : public APickUpItemBase
{
	GENERATED_BODY()
	
protected:

	virtual void PostInitializeComponents() override;

	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	void Interact_Implementation(APawn* InstigatorPawn) override;

	void ChangeInteractionState();
};
