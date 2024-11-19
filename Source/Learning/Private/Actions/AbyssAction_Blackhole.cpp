// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/AbyssAction_Blackhole.h"

#include "GameFramework/Character.h"
#include "Animations/Power1Notify.h"

UAbyssAction_Blackhole::UAbyssAction_Blackhole()
{
	HandSocketName = "Muzzle_01";
}

void UAbyssAction_Blackhole::AttackTimeElapsed(ACharacter* Instigator)
{
	FVector HandLocation = Instigator->GetMesh()->GetSocketLocation(HandSocketName);

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_PhysicsBody);

	FVector Start = Instigator->GetPawnViewLocation();
	FVector End = Start + (Instigator->GetControlRotation().Vector() * 1000);

	FHitResult Hit;
	bool bHit = GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, ObjectQueryParams);

	if (bHit)
	{
		End = Hit.ImpactPoint;
	}

	FVector Direction = (End - HandLocation).GetSafeNormal2D();
	FRotator ProjRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	ProjRotation.Pitch = 0;
	ProjRotation.Roll = 0;

	FTransform SpawnTransformMatrix = FTransform(ProjRotation, HandLocation);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	SpawnParameters.Instigator = Instigator;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransformMatrix, SpawnParameters);

	StopAction(Instigator);
}

void UAbyssAction_Blackhole::InitAnimations()
{
	if (AttackAnim)
	{
		const TArray<FAnimNotifyEvent> NotifyEvents = AttackAnim->Notifies;
		for (FAnimNotifyEvent N : NotifyEvents)
		{
			UPower1Notify* ProjectileAttackNotify = Cast<UPower1Notify>(N.Notify);
			if (ProjectileAttackNotify)
			{
				ProjectileAttackNotify->OnNotified.AddUObject(this, &UAbyssAction_Blackhole::AttackTimeElapsed);
			}
		}
	}
}

void UAbyssAction_Blackhole::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	if (!IsInitialized)
	{
		IsInitialized = true;
		InitAnimations();
	}

	ACharacter* Character = Cast<ACharacter>(Instigator);

	if (Character)
	{
		Character->PlayAnimMontage(AttackAnim);
	}
}
