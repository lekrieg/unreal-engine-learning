// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/KeyCard.h"

#include "Actions/AbyssActionComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Characters/AbyssAttributeComponent.h"

// Sets default values
AKeyCard::AKeyCard()
{
	KeyCardMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("KeyCardMesh");
	KeyCardMeshComp->SetupAttachment(RootComponent);
}

void AKeyCard::Interact_Implementation(APawn* InstigatorPawn)
{
	UAbyssActionComponent* ActionComp = InstigatorPawn->GetComponentByClass<UAbyssActionComponent>();

	if (ActionComp)
	{
		if (ensure(KeyCardTag.IsValid()))
		{
			ActionComp->ActiveGameplayTags.AddTag(KeyCardTag);

			UAbyssAttributeComponent* AttribComp = InstigatorPawn->GetComponentByClass<UAbyssAttributeComponent>();
			if (AttribComp)
			{
				AttribComp->UpdateObtainedKeycards(KeyCardTag);
			}

			SetLifeSpan(0.1f);
		}
	}
}