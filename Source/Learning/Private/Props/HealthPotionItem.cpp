// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/HealthPotionItem.h"
#include "Characters/AbyssAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

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
	if (bCanInteract && OtherActor)
	{
		UAbyssAttributeComponent* Comp = Cast<UAbyssAttributeComponent>(OtherActor->GetComponentByClass(UAbyssAttributeComponent::StaticClass()));

		if (Comp && !Comp->IsHealthFull())
		{
			PlaySound(PickUpSound);

			if (EmitterTemplate)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EmitterTemplate, GetActorLocation(), FRotator::ZeroRotator, true);
			}

			MeshComp->SetVisibility(!MeshComp->IsVisible());
			bCanInteract = false;

			Comp->ApplyHealthChange(this, ValueAmount);
			GetWorldTimerManager().SetTimer(TimerHandleChangeState, this, &AHealthPotionItem::ChangeInteractionState, 10.0f);
		}
	}
}

void AHealthPotionItem::Interact_Implementation(APawn* InstigatorPawn)
{
	if (bCanInteract && InstigatorPawn)
	{
		UAbyssAttributeComponent* Comp = Cast<UAbyssAttributeComponent>(InstigatorPawn->GetComponentByClass(UAbyssAttributeComponent::StaticClass()));

		if (Comp && !Comp->IsHealthFull())
		{
			PlaySound(PickUpSound);

			// TODO: Add credits costs
			// TODO: Add Coin animation
			// TODO: Add Coin credits earning
			// TODO: Add Coin effect
			// TODO: Add an eqs to randomly spawn health potions and Coins

			if (EmitterTemplate)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EmitterTemplate, GetActorLocation(), FRotator::ZeroRotator, true);
			}

			MeshComp->SetVisibility(!MeshComp->IsVisible());
			bCanInteract = false;

			Comp->ApplyHealthChange(this, ValueAmount);
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
