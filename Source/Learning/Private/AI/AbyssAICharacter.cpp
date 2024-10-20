// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AbyssAICharacter.h"

#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "AI/AbyssAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/AbyssAttributeComponent.h"
#include "DrawDebugHelpers.h"

AAbyssAICharacter::AAbyssAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");
	AttributeComp = CreateDefaultSubobject<UAbyssAttributeComponent>("AttribComp");
}

void AAbyssAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AAbyssAICharacter::OnPawnSeen);
	AttributeComp->OnHealthChanged.AddDynamic(this, &AAbyssAICharacter::OnHealthChanged);
}

void AAbyssAICharacter::OnPawnSeen(APawn* Pawn)
{
	AAIController* AIC = Cast<AAIController>(GetController());

	if (AIC)
	{
		 UBlackboardComponent* BBComp = AIC->GetBlackboardComponent();

		 BBComp->SetValueAsObject("TargetActor", Pawn);

		 DrawDebugString(GetWorld(), GetActorLocation(), "Player spotted!", nullptr, FColor::Orange, 4.0f, false);
	}
}

void AAbyssAICharacter::OnHealthChanged(AActor* InstigatorActor, UAbyssAttributeComponent* OwningComp, float NewHealth, float amount)
{
	if (amount < 0.0f)
	{
		if (NewHealth > 0)
		{
			USkeletalMeshComponent* MeshComp = GetMesh();
			MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
			MeshComp->SetScalarParameterValueOnMaterials("HitFlashSpeed", 4);
			MeshComp->SetVectorParameterValueOnMaterials("HitFlashColor", FVector(FColor::Red));
		}

		if (NewHealth <= 0.0f)
		{
			/*AAbyssAIController* AC = Cast<AAbyssAIController>(GetController());
			AC->UnPossess();
			AC->Destroy();
			Destroy();*/

			// TODO: Add timer to destroy enemy
		}
	}
}
