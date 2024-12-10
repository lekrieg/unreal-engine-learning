// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AbyssAICharacter.h"

#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "AI/AbyssAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/AbyssAttributeComponent.h"
#include "DrawDebugHelpers.h"
#include "BrainComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/AbyssWorldUserWidget.h"
#include "AbyssGameModeBase.h"

AAbyssAICharacter::AAbyssAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");
	AttributeComp = CreateDefaultSubobject<UAbyssAttributeComponent>("AttribComp");

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
}

void AAbyssAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AAbyssAICharacter::OnPawnSeen);
	AttributeComp->OnHealthChanged.AddDynamic(this, &AAbyssAICharacter::OnHealthChanged);
}

void AAbyssAICharacter::OnPawnSeen(APawn* Pawn)
{
	SetTargetActor(Pawn);
	
	DrawDebugString(GetWorld(), GetActorLocation(), "Player spotted!", nullptr, FColor::Orange, 4.0f, false);
}

void AAbyssAICharacter::OnHealthChanged(AActor* InstigatorActor, UAbyssAttributeComponent* OwningComp, float NewHealth, float amount)
{
	if (InstigatorActor)
	{
		SetTargetActor(InstigatorActor);

	}

	if (!ActiveHealthBar)
	{
		ActiveHealthBar = CreateWidget<UAbyssWorldUserWidget>(GetWorld(), HealthBarWidgetClass);

		if (ActiveHealthBar)
		{
			ActiveHealthBar->AttachedActor = this;
			ActiveHealthBar->AddToViewport();
		}
	}


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
			AAbyssAIController* AIC = Cast<AAbyssAIController>(GetController());
			if (AIC)
			{
				AIC->GetBrainComponent()->StopLogic("Killed");
			}

			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GetCharacterMovement()->DisableMovement();

			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");

			SetLifeSpan(10.0f);

			AAbyssGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AAbyssGameModeBase>();

			if (GameMode)
			{
				GameMode->ApplyCredits(GetOwner(), AttributeComp->GetCredits());
			}
		}
	}
}

void AAbyssAICharacter::SetTargetActor(AActor* NewTarget)
{
	AAIController* AIC = Cast<AAIController>(GetController());

	if (AIC)
	{
		AIC->GetBlackboardComponent()->SetValueAsObject("TargetActor", NewTarget);
	}
}
