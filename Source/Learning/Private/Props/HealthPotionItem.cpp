// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/HealthPotionItem.h"
#include "Characters/AbyssAttributeComponent.h"
#include "Components/SphereComponent.h"

void AHealthPotionItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (SphereComp)
	{
		SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AHealthPotionItem::OnActorOverlap);
	}
}

void AHealthPotionItem::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO: Add sound cue when pick up item
	// TODO: Add effect when pick up item
	// TODO: Ignore intection if healt if full

	if (bCanInteract && OtherActor)
	{
		UAbyssAttributeComponent* Comp = Cast<UAbyssAttributeComponent>(OtherActor->GetComponentByClass(UAbyssAttributeComponent::StaticClass()));

		if (Comp)
		{
			MeshComp->SetVisibility(!MeshComp->IsVisible());
			bCanInteract = false;

			Comp->ApplyHealthChange(ValueAmount);
			GetWorldTimerManager().SetTimer(TimerHandleChangeState, this, &AHealthPotionItem::ChangeInteractionState, 10.0f);
		}
	}
}

void AHealthPotionItem::Interact_Implementation(APawn* InstigatorPawn)
{
	if (bCanInteract && InstigatorPawn)
	{
		UAbyssAttributeComponent* Comp = Cast<UAbyssAttributeComponent>(InstigatorPawn->GetComponentByClass(UAbyssAttributeComponent::StaticClass()));

		if (Comp)
		{
			MeshComp->SetVisibility(!MeshComp->IsVisible());
			bCanInteract = false;

			Comp->ApplyHealthChange(ValueAmount);
			GetWorldTimerManager().SetTimer(TimerHandleChangeState, this, &AHealthPotionItem::ChangeInteractionState, 10.0f);
		}
	}
}

void AHealthPotionItem::ChangeInteractionState()
{
	if (MeshComp)
	{
		MeshComp->SetVisibility(!MeshComp->IsVisible());
	}

	bCanInteract = !bCanInteract;
}
