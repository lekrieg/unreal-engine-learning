// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/AbyssActionComponent.h"

#include "Actions/AbyssAction.h"

// Sets default values for this component's properties
UAbyssActionComponent::UAbyssActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UAbyssActionComponent::BeginPlay()
{
	Super::BeginPlay();

	for (TSubclassOf<UAbyssAction> ActionClass : DefaultActions)
	{
		AddAction(ActionClass);
	}
}

// Called every frame
void UAbyssActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FString DebugMessage = GetNameSafe(GetOwner()) + " : " + ActiveGameplayTags.ToStringSimple();
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, DebugMessage);
}

void UAbyssActionComponent::AddAction(TSubclassOf<UAbyssAction> ActionClass)
{
	if (!ensure(ActionClass))
	{
		return;
	}

	UAbyssAction* NewAction = NewObject<UAbyssAction>(this, ActionClass);

	if (ensure(NewAction))
	{
		Actions.Add(NewAction);
	}
}

bool UAbyssActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
	for (UAbyssAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (!Action->CanStart(Instigator))
			{
				FString FailedMessage = FString::Printf(TEXT("Failed to run: %s"), *ActionName.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FailedMessage);
				continue;
			}

			Action->StartAction(Instigator);
			return true;
		}
	}

	return false;
}

bool UAbyssActionComponent::StopActionByName(AActor* Instigator, FName ActionName)
{
	for (UAbyssAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (Action->IsRunning())
			{
				Action->StopAction(Instigator);
				return true;
			}
		}
	}

	return false;
}