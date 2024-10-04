// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbyssProjectileBase.h"
#include "AbyssMagicProjectile.generated.h"

UCLASS()
class LEARNING_API AAbyssMagicProjectile : public AAbyssProjectileBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbyssMagicProjectile();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) override;

	virtual void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

};
