// Fill out your copyright notice in the Description page of Project Settings.


#include "AbyssPlayerState.h"

void AAbyssPlayerState::ApplyCreditsChange(AActor* InstigatorActor, float Amount)
{
	Credits += Amount;
	
	if (Credits < 0.0f)
	{
		Credits = 0.0f;
	}

	OnCreditsChanged.Broadcast(InstigatorActor, Credits);
}

float AAbyssPlayerState::GetCredits() const
{
	return Credits;
}
