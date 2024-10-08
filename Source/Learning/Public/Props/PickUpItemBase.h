// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/AbyssGameplayInterface.h"
#include "PickUpItemBase.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS(ABSTRACT)
class LEARNING_API APickUpItemBase : public AActor, public IAbyssGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpItemBase();

protected:

	FTimerHandle TimerHandleChangeState;
	bool bCanInteract;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ValueAmount;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void Interact_Implementation(APawn* InstigatorPawn);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
