// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/ExplosiveBarril.h"

#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Characters/AbyssAttributeComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AExplosiveBarril::AExplosiveBarril()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->ImpulseStrength = 2000.0f;
	RadialForceComp->Radius = 600;
	RadialForceComp->bImpulseVelChange = true;

	RadialForceComp->SetupAttachment(MeshComp);
}

void AExplosiveBarril::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	MeshComp->OnComponentHit.AddDynamic(this, &AExplosiveBarril::MyFireImpulse);
}

void AExplosiveBarril::MyFireImpulse(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UAbyssAttributeComponent* comp = Cast<UAbyssAttributeComponent>(OtherActor->GetComponentByClass(UAbyssAttributeComponent::StaticClass()));

	if (comp)
	{
		comp->ApplyHealthChange(-30.0f);
	}

	RadialForceComp->FireImpulse();

	UE_LOG(LogTemp, Log, TEXT("EXPLOSION!"));

	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, at game time: %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);

	FString CombinedString = FString::Printf(TEXT("Hit at location: %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 2.0f, true);
}
