// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/AbyssDash.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/AbyssCharacter.h"

// Called when the game starts or when spawned
void AAbyssDash::BeginPlay()
{
	Super::BeginPlay();

	PlaySound(FlightSound);
	GetWorldTimerManager().SetTimer(TimerHandleExplosion, this, &AAbyssDash::Explode, 0.2f);
}

void AAbyssDash::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComp->OnComponentHit.AddDynamic(this, &AAbyssDash::OnActorHit);
}

void AAbyssDash::Explode()
{
	ProjectileMovementComp->StopMovementImmediately();

	EffectComp->Deactivate();

	if (ensure(EmitterTemplate))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EmitterTemplate, GetActorLocation(), FRotator::ZeroRotator, true);
	}

	PlaySound(ExplosionSound);

	//GetInstigator();
	GetWorldTimerManager().ClearTimer(TimerHandleExplosion);
	GetWorldTimerManager().SetTimer(TimerHandleExplosion, this, &AAbyssDash::TeleportPlayer, 0.2f);
}

void AAbyssDash::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

void AAbyssDash::TeleportPlayer()
{
	AAbyssCharacter* player = Cast<AAbyssCharacter>(GetInstigator());
	player->SetActorRelativeLocation(GetActorLocation(), true);

	Destroy();
}