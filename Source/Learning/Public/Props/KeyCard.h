// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/AbyssGameplayInterface.h"
#include "GameplayTagsClasses.h"
#include "KeyCard.generated.h"

class UStaticMeshComponent;

UCLASS()

class LEARNING_API AKeyCard : public AActor, public IAbyssGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKeyCard();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* KeyCardMeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tags")
	FGameplayTag KeyCardTag;

	void Interact_Implementation(APawn* InstigatorPawn);

};