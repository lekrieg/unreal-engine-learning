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

}

// Called every frame
void AAbyssBlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AAbyssBlackHole::AAbyssBlackHole() : Super()
{
	SphereComp->SetCollisionObjectType(ECC_PhysicsBody);

	ProjectileMovementComp->ProjectileGravityScale = 0.0f;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->bImpulseVelChange = false;
	RadialForceComp->ForceStrength = -20000.0f;
	RadialForceComp->Radius = 600;

	RadialForceComp->SetupAttachment(SphereComp);
}
