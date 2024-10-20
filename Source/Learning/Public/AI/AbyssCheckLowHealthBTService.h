// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "AbyssCheckLowHealthBTService.generated.h"

/**
 * 
 */
UCLASS()
class LEARNING_API UAbyssCheckLowHealthBTService : public UBTService
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, Category = "AI stuff")
	FBlackboardKeySelector LowHealthRangeKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
