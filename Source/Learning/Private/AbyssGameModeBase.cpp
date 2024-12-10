// Fill out your copyright notice in the Description page of Project Settings.


#include "AbyssGameModeBase.h"

#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "Logging/LogMacros.h"
#include "AI/AbyssAICharacter.h"
#include "Characters/AbyssCharacter.h"
#include "Characters/AbyssAttributeComponent.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"
#include "AbyssPlayerState.h"
#include "Kismet/GameplayStatics.h"

static TAutoConsoleVariable<bool> CVarSpawnBots(TEXT("abyss.SpawnBots"), true, TEXT("Enable spawning of bots via timer."), ECVF_Cheat);

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
	if (CVarSpawnBots.GetValueOnGameThread())
	{
		UE_LOG(LogTemp, Warning, TEXT("Bot spawning disabled via cvar 'CVarSpawBots'."));

		return;
	}
	int32 NumberOfAliveBots = 4;
	for (TActorIterator<AAbyssAICharacter> It(GetWorld()); It; ++It)
	{
		AAbyssAICharacter* Bot = *It;

		UAbyssAttributeComponent* AttributeComp = UAbyssAttributeComponent::GetAttributeComp(Bot);

		if (AttributeComp && AttributeComp->IsAlive())
		{
			NumberOfAliveBots++;
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Found %i alive bots"), NumberOfAliveBots);

	//float MaxBotCount = 10.0f;
	float MaxBotCount = 1.0f;

	if (DifficultyCurve)
	{
		MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}

	if (NumberOfAliveBots >= MaxBotCount)
	{
		UE_LOG(LogTemp, Log, TEXT("At maximum bot capacity. Skipping bot spawn!"));
		return;
	}

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

	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

	if (Locations.Num() > 0)
	{
		GetWorld()->SpawnActor<AActor>(MinionRangedClass, Locations[0], FRotator::ZeroRotator);

		DrawDebugSphere(GetWorld(), Locations[0], 50.0f, 20, FColor::Blue, false, 60.0);
	}
}

void AAbyssGameModeBase::RespawnPlayerElapsed(AController* Controller)
{
	if (ensure(Controller))
	{
		Controller->UnPossess();
		RestartPlayer(Controller);
	}
}

void AAbyssGameModeBase::OnActorKilled(AActor* VictimActor, AActor* Killer)
{
	// TODO: Fix this thing, the spawn is bugged
	AAbyssCharacter* Player = Cast<AAbyssCharacter>(VictimActor);

	if (Player)
	{
		FTimerHandle TimerHandleRespawnDelay;

		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "RespawnPlayerElapsed", Player->GetController());
		//Delegate.BindUObject(this, &AAbyssGameModeBase::RespawnPlayerElapsed, Player->GetController());

		float RespawnDelay = 2.0f;
		GetWorldTimerManager().SetTimer(TimerHandleRespawnDelay, Delegate, RespawnDelay, false);
	}

	UE_LOG(LogTemp, Log, TEXT("OnActorKilled: Victim: %s, Killer: %s"), *GetNameSafe(VictimActor), *GetNameSafe(Killer));
}

void AAbyssGameModeBase::ApplyCredits(AActor* FuckThisShit, float Amount)
{
	AAbyssPlayerState* AbyssPlayerState = Cast<AAbyssPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));

	if (AbyssPlayerState)
	{
		AbyssPlayerState->ApplyCreditsChange(FuckThisShit, Amount);
	}
}
