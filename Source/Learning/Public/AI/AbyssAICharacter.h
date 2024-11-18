// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "AbyssAICharacter.generated.h"

// there's the perception too, check this later
class UPawnSensingComponent;
class UAbyssAttributeComponent;
class UUserWidget;
class UAbyssWorldUserWidget;

UCLASS()
class LEARNING_API AAbyssAICharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AAbyssAICharacter();

protected:

	UAbyssWorldUserWidget* ActiveHealthBar;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> HealthBarWidgetClass;

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
