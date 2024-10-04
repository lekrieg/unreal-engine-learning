// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/AbyssMagicProjectile.h"
#include "AbyssProjectileBase.h"
#include "AbyssDash.generated.h"

class UParticleSystem;

UCLASS()
class LEARNING_API AAbyssDash : public AAbyssProjectileBase
{
	GENERATED_BODY()
	
protected:

	FTimerHandle TimerHandleExplosion;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	void Explode();

	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) override;

	void TeleportPlayer();
};
