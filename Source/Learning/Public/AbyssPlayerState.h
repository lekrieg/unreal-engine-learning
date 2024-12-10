// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbyssPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCreditsChanged, AActor*, InstigatorActor, float, Amount);

UCLASS()
class LEARNING_API AAbyssPlayerState : public APlayerState
{
	GENERATED_BODY()

private:
	float Credits;

public:
	
	UPROPERTY(BlueprintAssignable)
	// TODO: Register this event on the UI
	FOnCreditsChanged OnCreditsChanged;

	void ApplyCreditsChange(AActor* InstigatorActor, float Amount);

	UFUNCTION(BlueprintCallable)
	float GetCredits() const;
};
