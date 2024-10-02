// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbyssTargetDummy.generated.h"

class UAbyssAttributeComponent;
class UStaticMeshComponent;

UCLASS()
class LEARNING_API AAbyssTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AAbyssTargetDummy();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute")
	UAbyssAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComp;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UAbyssAttributeComponent* OwningComp, float NewHealth, float amount);

};
