// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/ProjectileAttackNotify.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimSequenceBase.h"

void UProjectileAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	OnNotified.Broadcast();

	Super::Notify(MeshComp, Animation, EventReference);
}