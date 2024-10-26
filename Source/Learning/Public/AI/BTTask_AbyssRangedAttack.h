// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_AbyssRangedAttack.generated.h"

/**
 * 
 */
UCLASS()
class LEARNING_API UBTTask_AbyssRangedAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UBTTask_AbyssRangedAttack();

protected:

	UPROPERTY(EditAnywhere, Category = "AI")
	float MaxBulletSpread;

	UPROPERTY(EditAnywhere, Category = "AI")
	TSubclassOf<AActor> ProjectileClass;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
