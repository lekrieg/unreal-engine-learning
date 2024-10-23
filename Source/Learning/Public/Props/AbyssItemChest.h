// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/AbyssGameplayInterface.h"
#include "AbyssItemChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class LEARNING_API AAbyssItemChest : public AActor, public IAbyssGameplayInterface
{
	GENERATED_BODY()

	void Interact_Implementation(APawn* InstigatorPawn);
	
public:	
	// Sets default values for this actor's properties
	AAbyssItemChest();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh")
	UStaticMeshComponent* BaseMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* LidMeshComp;

public:	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Lid stuff")
	float TargetPitch = 110;

};
