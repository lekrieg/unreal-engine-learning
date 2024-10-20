// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_AbyssHealAI.h"

#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/AbyssAttributeComponent.h"

EBTNodeResult::Type UBTTask_AbyssHealAI::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyController = OwnerComp.GetAIOwner();

	if (ensure(MyController))
	{
		ACharacter* MyPawn = Cast<ACharacter>(MyController->GetPawn());
		if (!MyPawn)
		{
			return EBTNodeResult::Failed;
		}

		UAbyssAttributeComponent* comp = Cast<UAbyssAttributeComponent>(MyPawn->GetComponentByClass(UAbyssAttributeComponent::StaticClass()));
		comp->ApplyHealthChange(40);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
