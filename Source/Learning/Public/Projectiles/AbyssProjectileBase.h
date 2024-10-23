// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbyssProjectileBase.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class UParticleSystem;
class UAudioComponent;
class USoundCue;

UCLASS(ABSTRACT)
class LEARNING_API AAbyssProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbyssProjectileBase();

protected:

	FTimerHandle TimerHandleDestroy;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* ProjectileMovementComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Emitter stuff")
	UParticleSystemComponent* EffectComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Emitter stuff")
	UParticleSystem* EmitterTemplate;

	// SFX STUFF
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio stuff")
	UAudioComponent* AudioComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio stuff")
	USoundCue* FlightSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio stuff")
	USoundCue* ExplosionSound;

	UPROPERTY(EditAnywhere, Category = "Damage stuff")
	float Damage = 40.0f;
	
	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	virtual void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void PostInitializeComponents() override;

	void SelfDestroy();

	void PlaySound(USoundCue* sound);

};
