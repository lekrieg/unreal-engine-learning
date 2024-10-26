// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbyssAICharacter.generated.h"

// there's the perception too, check this later
class UPawnSensingComponent;
class UAbyssAttributeComponent;

UCLASS()
class LEARNING_API AAbyssAICharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AAbyssAICharacter();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute")
	UAbyssAttributeComponent* AttributeComp;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UAbyssAttributeComponent* OwningComp, float NewHealth, float amount);

	void SetTargetActor(AActor* NewTarget);
};
