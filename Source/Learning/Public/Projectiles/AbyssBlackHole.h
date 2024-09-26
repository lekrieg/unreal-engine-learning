// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/AbyssMagicProjectile.h"
#include "AbyssBlackHole.generated.h"

class URadialForceComponent;

/**
 * 
 */
UCLASS()
class LEARNING_API AAbyssBlackHole : public AAbyssMagicProjectile
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	URadialForceComponent* RadialForceComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AAbyssBlackHole();
};
