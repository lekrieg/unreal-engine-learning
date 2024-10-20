// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AbyssAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AAbyssAIController::BeginPlay()
{
	Super::BeginPlay();

	if (ensureMsgf(BehaviorTree, TEXT("Behavior tree is nullptr! Please assign behavior tree in your ai controller.")))
	{
		RunBehaviorTree(BehaviorTree);
	}

	//APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	//if (MyPawn)
	//{
	//	GetBlackboardComponent()->SetValueAsVector("MoveToLocation", MyPawn->GetActorLocation());

	//	GetBlackboardComponent()->SetValueAsObject("TargetActor", MyPawn);
	//}
}
