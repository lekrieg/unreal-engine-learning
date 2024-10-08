// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/AbyssProjectileBase.h"

#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Characters/AbyssAttributeComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

AAbyssProjectileBase::AAbyssProjectileBase()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	//SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	//SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	//SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	AudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComp");
	AudioComp->SetupAttachment(SphereComp);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComp");
	ProjectileMovementComp->InitialSpeed = 1000.0f;
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->bInitialVelocityInLocalSpace = true;
}

void AAbyssProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!IsPendingKillPending())
	{
		if (EmitterTemplate)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EmitterTemplate, GetActorLocation(), FRotator::ZeroRotator, true);
		}

		GetWorldTimerManager().SetTimer(TimerHandleDestroy, this, &AAbyssProjectileBase::SelfDestroy, 1.0f);
	}
}

void AAbyssProjectileBase::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AAbyssProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (SphereComp)
	{
		SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	}
}

void AAbyssProjectileBase::SelfDestroy()
{
	GetWorldTimerManager().ClearTimer(TimerHandleDestroy);
	Destroy();
}

void AAbyssProjectileBase::PlaySound(USoundCue* sound)
{
	if (AudioComp && sound)
	{
		AudioComp->SetSound(sound);
		AudioComp->Play();
	}
}
