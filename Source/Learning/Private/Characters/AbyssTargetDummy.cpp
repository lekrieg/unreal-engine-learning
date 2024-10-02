// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AbyssTargetDummy.h"

#include "Characters/AbyssAttributeComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AAbyssTargetDummy::AAbyssTargetDummy()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	AttributeComp = CreateDefaultSubobject<UAbyssAttributeComponent>("AttributeComp");
	AttributeComp->OnHealthChanged.AddDynamic(this, &AAbyssTargetDummy::OnHealthChanged);
}

void AAbyssTargetDummy::OnHealthChanged(AActor* InstigatorActor, UAbyssAttributeComponent* OwningComp, float NewHealth, float amount)
{
	if (amount < 0.0f)
	{
		MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
}