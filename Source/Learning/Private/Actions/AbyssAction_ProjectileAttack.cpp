// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/AbyssAction_ProjectileAttack.h"

#include "GameFramework/Character.h"
#include "Animations/ProjectileAttackNotify.h"

UAbyssAction_ProjectileAttack::UAbyssAction_ProjectileAttack()
{
	HandSocketName = "Muzzle_01";
}

void UAbyssAction_ProjectileAttack::AttackTimeElapsed(ACharacter* Instigator)
{
	FVector HandLocation = Instigator->GetMesh()->GetSocketLocation(HandSocketName);

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);

	FVector Start = Instigator->GetPawnViewLocation();
	FVector End = Start + (Instigator->GetControlRotation().Vector() * 1000);

	FHitResult Hit;
	bool bHit = GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, ObjectQueryParams);

	if (bHit)
	{
		UE_LOG(LogTemp, Log, TEXT("OtherActor: %s, at game time: %f"), *GetNameSafe(Hit.GetActor()), GetWorld()->TimeSeconds);
		End = Hit.ImpactPoint;
	}

	FColor LineColor = bHit ? FColor::Green : FColor::Red;
	DrawDebugLine(GetWorld(), Start, End, LineColor, false, 2.0f, 0, 2.0f);

	//FVector Direction = (Hit.ImpactPoint - HandLocation).GetSafeNormal();
	FRotator ProjRotation = FRotationMatrix::MakeFromX(End - HandLocation).Rotator();

	FTransform SpawnTransformMatrix = FTransform(ProjRotation, HandLocation);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	SpawnParameters.Instigator = Instigator;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransformMatrix, SpawnParameters);

	StopAction(Instigator);
}

void UAbyssAction_ProjectileAttack::InitAnimations()
{
	if (AttackAnim)
	{
		// TODO: this thing is bugging the attack if I use the dash and the attack after
		const TArray<FAnimNotifyEvent> NotifyEvents = AttackAnim->Notifies;
		for (FAnimNotifyEvent N : NotifyEvents)
		{
			UProjectileAttackNotify* ProjectileAttackNotify = Cast<UProjectileAttackNotify>(N.Notify);
			if (ProjectileAttackNotify)
			{
				ProjectileAttackNotify->OnNotified.AddUObject(this, &UAbyssAction_ProjectileAttack::AttackTimeElapsed);
			}
		}
	}
}

void UAbyssAction_ProjectileAttack::StartAction_Implementation(AActor* Instigator)
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
