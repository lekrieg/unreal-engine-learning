// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AbyssAttributeComponent.h"

// Sets default values for this component's properties
UAbyssAttributeComponent::UAbyssAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Health = 100.0f;
}

bool UAbyssAttributeComponent::ApplyHealthChange(float amount)
{
	Health += amount;

	OnHealthChanged.Broadcast(nullptr, this, Health, amount);

	return true;
}

bool UAbyssAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

