// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/AbyssBlackHole.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Called when the game starts or when spawned
void AAbyssBlackHole::BeginPlay()
{
	Super::BeginPlay();

	PlaySound(FlightSound);

	GetWorldTimerManager().SetTimer(TimerHandleDestroy, this, &AAbyssBlackHole::SelfDestroy, 5.0f);
}

void AAbyssBlackHole::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PlaySound(ExplosionSound);
	if (OtherActor->GetRootComponent()->IsSimulatingPhysics())
	{
		OtherActor->Destroy();
	}
}

void AAbyssBlackHole::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AAbyssBlackHole::OnActorOverlap);
}

AAbyssBlackHole::AAbyssBlackHole()
{
	SphereComp->SetCollisionObjectType(ECC_PhysicsBody);

	ProjectileMovementComp->ProjectileGravityScale = 0.0f;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->bImpulseVelChange = false;
	RadialForceComp->ForceStrength = -20000.0f;
	RadialForceComp->Radius = 600;

	RadialForceComp->SetupAttachment(SphereComp);
}
