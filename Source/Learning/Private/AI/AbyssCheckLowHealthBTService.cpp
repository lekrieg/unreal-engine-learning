// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AbyssCheckLowHealthBTService.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Characters/AbyssAttributeComponent.h"

void UAbyssCheckLowHealthBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackBoardComp))
	{
		AAIController* MyController = OwnerComp.GetAIOwner();
		if (ensure(MyController))
		{
			APawn* AIPawn = MyController->GetPawn();
			if (ensure(AIPawn))
			{
				UAbyssAttributeComponent* comp = Cast<UAbyssAttributeComponent>(AIPawn->GetComponentByClass(UAbyssAttributeComponent::StaticClass()));
				bool bLowHealth = comp->GetActualHealth() <= 35.0f;

				BlackBoardComp->SetValueAsBool(LowHealthRangeKey.SelectedKeyName, bLowHealth);
			}
		}
	}
}
