// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/AbyssMagicProjectile.h"
#include "AbyssProjectileBase.h"
#include "AbyssBlackHole.generated.h"

class URadialForceComponent;

/**
 * 
 */
UCLASS()
class LEARNING_API AAbyssBlackHole : public AAbyssProjectileBase
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	URadialForceComponent* RadialForceComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	virtual void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

public:

	AAbyssBlackHole();
};
