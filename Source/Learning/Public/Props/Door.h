// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/AbyssGameplayInterface.h"
#include "GameplayTagsClasses.h"
#include "Door.generated.h"

class UStaticMeshComponent;
class UAbyssInteractionComponent;

UCLASS()
class LEARNING_API ADoor : public AActor, public IAbyssGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* DoorHallMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* DoorMeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tags")
	FGameplayTag KeyCardTag;
};
