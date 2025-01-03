// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/AbyssMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Characters/AbyssAttributeComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "DrawDebugHelpers.h"
#include "AbyssGameplayFunctionLibrary.h"

// Sets default values
AAbyssMagicProjectile::AAbyssMagicProjectile()
{

}

// Called when the game starts or when spawned
void AAbyssMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	PlaySound(FlightSound);
}

void AAbyssMagicProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AAbyssMagicProjectile::OnActorOverlap);
	SphereComp->OnComponentHit.AddDynamic(this, &AAbyssMagicProjectile::OnActorHit);
}

void AAbyssMagicProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Damage, 8, FColor::White, false, 1.0f, 0, 2.0f);

	PlaySound(ExplosionSound);

	Super::OnActorHit(HitComponent, OtherActor, OtherComponent, NormalImpulse, Hit);
}

void AAbyssMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		/*UAbyssAttributeComponent* comp = UAbyssAttributeComponent::GetAttributeComp(OtherActor);

		if (comp)
		{
			comp->ApplyHealthChange(GetInstigator(), -Damage);

			SelfDestroy();
		}*/

		// TODO: Fix this, seems that the impulse isn't being applied
		if (UAbyssGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, Damage, SweepResult))
		{
			SelfDestroy();
		}
	}
}