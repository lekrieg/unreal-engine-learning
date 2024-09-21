// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/AbyssItemChest.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
AAbyssItemChest::AAbyssItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("BaseMeshComp");
	RootComponent = BaseMeshComp;

	LidMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("LitMeshComp");
	LidMeshComp->SetupAttachment(BaseMeshComp);

}

// Called when the game starts or when spawned
void AAbyssItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAbyssItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAbyssItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMeshComp->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
}

