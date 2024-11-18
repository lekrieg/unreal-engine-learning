// Fill out your copyright notice in the Description page of Project Settings.


#include "AbyssGameplayFunctionLibrary.h"

#include "Characters/AbyssAttributeComponent.h"

bool UAbyssGameplayFunctionLibrary::ApplyDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount)
{
	UAbyssAttributeComponent* AttributeComp = UAbyssAttributeComponent::GetAttributeComp(TargetActor);
	if (AttributeComp)
	{
		AttributeComp->ApplyHealthChange(DamageCauser, -DamageAmount);
		return true;
	}

	return false;
}

bool UAbyssGameplayFunctionLibrary::ApplyDirectionalDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount, const FHitResult& HitResult)
{
	bool test = ApplyDamage(DamageCauser, TargetActor, DamageAmount);
	if (test)
	{
		UPrimitiveComponent* HitComp = HitResult.GetComponent();

		if (HitComp && HitComp->IsSimulatingPhysics(HitResult.BoneName))
		{
			FVector Direction = HitResult.TraceEnd - HitResult.TraceStart;
			Direction.Normalize();

			UE_LOG(LogTemp, Log, TEXT("Impulse force: %s"), *(-HitResult.ImpactNormal * 300000.0f).ToString());
			HitComp->AddImpulseAtLocation(Direction * 300000.0f, HitResult.ImpactPoint, HitResult.BoneName);
		}

		return true;
	}

	return false;
}
