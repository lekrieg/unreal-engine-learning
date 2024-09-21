// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/ExplosiveBarril.h"

#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

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

// Called when the game starts or when spawned
void AExplosiveBarril::BeginPlay()
{
	Super::BeginPlay();

	MeshComp->OnComponentHit.AddDynamic(this, &AExplosiveBarril::MyFireImpulse);
	
}

void AExplosiveBarril::MyFireImpulse(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComp->FireImpulse();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("EXPLOSION!"));
	}
}

// Called every frame
void AExplosiveBarril::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

