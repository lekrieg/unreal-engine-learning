// Fill out your copyright notice in the Description page of Project Settings.


#include "AbyssGameModeBase.h"

#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "Logging/LogMacros.h"
#include "AI/AbyssAICharacter.h"
#include "Characters/AbyssAttributeComponent.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"

AAbyssGameModeBase::AAbyssGameModeBase()
{
	SpawnTimerInterval = 2.0f;
}

void AAbyssGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandleSpawnBots, this, &AAbyssGameModeBase::SpawnBotTimerElapsed, SpawnTimerInterval, true);
}

void AAbyssGameModeBase::SpawnBotTimerElapsed()
{
	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);

	if (ensure(QueryInstance))
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &AAbyssGameModeBase::OnQueryCompleted);
	}
}

void AAbyssGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn bot EQS query failed!"));
		return;
	}

	int32 NumberOfAliveBots = 0;
	for (TActorIterator<AAbyssAICharacter> It(GetWorld()); It; ++It)
	{
		AAbyssAICharacter* Bot = *It;

		UAbyssAttributeComponent* AttributeComp = Cast<UAbyssAttributeComponent>(Bot->GetComponentByClass(UAbyssAttributeComponent::StaticClass()));

		if (AttributeComp && AttributeComp->IsAlive())
		{
			NumberOfAliveBots++;
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Found %i alive bots"), NumberOfAliveBots);

	float MaxBotCount = 10.0f;

	if (DifficultyCurve)
	{
		MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}

	if (NumberOfAliveBots >= MaxBotCount)
	{
		UE_LOG(LogTemp, Log, TEXT("At maximum bot capacity. Skipping bot spawn!"));
		return;
	}

	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

	if (Locations.Num() > 0)
	{
		GetWorld()->SpawnActor<AActor>(MinionRangedClass, Locations[0], FRotator::ZeroRotator);

		DrawDebugSphere(GetWorld(), Locations[0], 50.0f, 20, FColor::Blue, false, 60.0);
	}
}
