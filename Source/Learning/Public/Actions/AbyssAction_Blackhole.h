// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/AbyssAction.h"
#include "AbyssAction_Blackhole.generated.h"

/**
 * 
 */
UCLASS()
class LEARNING_API UAbyssAction_Blackhole : public UAbyssAction
{
	GENERATED_BODY()
	
public:

	UAbyssAction_Blackhole();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack stuff")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack stuff")
	FName HandSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack stuff")
	UAnimMontage* AttackAnim;

	UFUNCTION()
	void AttackTimeElapsed(ACharacter* Instigator);

	void InitAnimations();

private:

	bool IsInitialized = false;

public:

	virtual void StartAction_Implementation(AActor* Instigator) override;
};
