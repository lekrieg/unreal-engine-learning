// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/KeyCard.h"

#include "Actions/AbyssActionComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AKeyCard::AKeyCard()
{
	KeyCardMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("KeyCardMesh");
	KeyCardMeshComp->SetupAttachment(RootComponent);
}

void AKeyCard::Interact_Implementation(APawn* InstigatorPawn)
{
	UAbyssActionComponent* AttribComp = InstigatorPawn->GetComponentByClass<UAbyssActionComponent>();

	if (AttribComp)
	{
		if (ensure(KeyCardTag.IsValid()))
		{
			AttribComp->ActiveGameplayTags.AddTag(KeyCardTag);
			SetLifeSpan(0.1f);
		}
	}
}