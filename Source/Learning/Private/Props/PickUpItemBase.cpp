// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/PickUpItemBase.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APickUpItemBase::APickUpItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetGenerateOverlapEvents(true);
	SphereComp->SetSphereRadius(32);
	RootComponent = SphereComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetupAttachment(SphereComp);

	bCanInteract = true;
}

// Called when the game starts or when spawned
void APickUpItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickUpItemBase::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void APickUpItemBase::Interact_Implementation(APawn* InstigatorPawn)
{
}

// Called every frame
void APickUpItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}