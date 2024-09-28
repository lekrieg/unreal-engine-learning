// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/AbyssMagicProjectile.h"
#include "AbyssDash.generated.h"

class UParticleSystem;

UCLASS()
class LEARNING_API AAbyssDash : public AAbyssMagicProjectile
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Emitter stuff")
	UParticleSystem* EmitterTemplate;

	FTimerHandle TimerHandleExplosion;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	void Explode();

	UFUNCTION()
	void ExplodeOnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void TeleportPlayer();

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
