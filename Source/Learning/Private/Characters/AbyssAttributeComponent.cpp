// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AbyssAttributeComponent.h"

#include "AbyssGameModeBase.h"
#include "Components/ActorComponent.h"
#include "GameplayTagsClasses.h"

static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("abyss.DamageMultiplier"), 1.0f, TEXT("Global damage modifier for attribute component."), ECVF_Cheat);

// Sets default values for this component's properties
UAbyssAttributeComponent::UAbyssAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxHealth = 100.0f;
	Health = MaxHealth;
}

// TODO: I can try to modify this to be a interface method that returns the comp reference in the actor
UAbyssAttributeComponent* UAbyssAttributeComponent::GetAttributeComp(AActor* TargetActor)
{
	if (TargetActor)
	{
		return TargetActor->GetComponentByClass<UAbyssAttributeComponent>();
	}

	return nullptr;
}

bool UAbyssAttributeComponent::CheckIfActorIsAlive(AActor* TargetActor)
{
	UAbyssAttributeComponent* AttribComp = GetAttributeComp(TargetActor);
	if (AttribComp)
	{
		return AttribComp->IsAlive();
	}
	return false;
}

bool UAbyssAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float amount)
{
	if (amount < 0.0f)
	{
		float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();

		amount *= DamageMultiplier;
	}

	Health += amount;

	Health = FMath::Clamp(Health, 0, MaxHealth);

	UE_LOG(LogTemp, Log, TEXT("Bot Health: %f"), Health);

	OnHealthChanged.Broadcast(InstigatorActor, this, Health, amount);

	if (!IsAlive())
	{
		AAbyssGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AAbyssGameModeBase>();

		if (GameMode)
		{
			GameMode->OnActorKilled(GetOwner(), InstigatorActor);
		}
	}

	return IsAlive();
}

bool UAbyssAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

bool UAbyssAttributeComponent::IsHealthFull() const
{
	return Health >= MaxHealth;
}

float UAbyssAttributeComponent::GetActualHealth() const
{
	return Health;
}

float UAbyssAttributeComponent::GetCredits() const
{
	return Credits;
}

void UAbyssAttributeComponent::UpdateObtainedKeycards(FGameplayTag KeyCardTag)
{
	if (KeyCardTag == UGameplayTagsManager::Get().RequestGameplayTag("KeyCards.Blue"))
	{
		bHasBlueKey = !bHasBlueKey;
	}
	else if (KeyCardTag == UGameplayTagsManager::Get().RequestGameplayTag("KeyCards.Red"))
	{
		bHasRedKey = !bHasRedKey;
	}
	else if (KeyCardTag == UGameplayTagsManager::Get().RequestGameplayTag("KeyCards.Green"))
	{
		bHasGreenKey = !bHasGreenKey;
	}
}
