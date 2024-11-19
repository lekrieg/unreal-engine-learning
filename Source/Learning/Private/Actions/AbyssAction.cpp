// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/AbyssAction.h"

#include "Actions/AbyssActionComponent.h"

void UAbyssAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Running: %s"), *GetNameSafe(this));

	UAbyssActionComponent* Comp = GetOwningComponent();

	Comp->ActiveGameplayTags.AppendTags(GrantsTags);

	bIsRunning = true;
}

void UAbyssAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Stopped: %s"), *GetNameSafe(this));

	ensureAlways(bIsRunning);

	UAbyssActionComponent* Comp = GetOwningComponent();

	Comp->ActiveGameplayTags.RemoveTags(GrantsTags);

	bIsRunning = false;
}

UAbyssActionComponent* UAbyssAction::GetOwningComponent() const
{
	return Cast<UAbyssActionComponent>(GetOuter());
}

bool UAbyssAction::IsRunning() const
{
	return bIsRunning;
}

bool UAbyssAction::CanStart_Implementation(AActor* Instigator)
{
	if (IsRunning())
	{
		return false;
	}

	UAbyssActionComponent* Comp = GetOwningComponent();
	if (Comp->ActiveGameplayTags.HasAny(BlockedTags))
	{
		return false;
	}

	return true;
}

UWorld* UAbyssAction::GetWorld() const
{
	UActorComponent* Comp = GetOwningComponent();

	if (Comp)
	{
		return Comp->GetWorld();
	}

	return nullptr;
}
