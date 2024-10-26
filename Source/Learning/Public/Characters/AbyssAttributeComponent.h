// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Delegates/DelegateCombinations.h"
#include "AbyssAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, UAbyssAttributeComponent*, OwningComp, float, NewHealth, float, amount);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEARNING_API UAbyssAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbyssAttributeComponent();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
	float MaxHealth;

public:

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	static UAbyssAttributeComponent* GetAttributeComp(AActor* TargetActor);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	static bool CheckIfActorIsAlive(AActor* TargetActor);

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	bool ApplyHealthChange(AActor* InstigatorActor, float amount);

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	bool IsHealthFull() const;

	UFUNCTION(BlueprintCallable)
	float GetActualHealth() const;

};
