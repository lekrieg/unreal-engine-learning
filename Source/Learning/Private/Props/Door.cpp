// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/Door.h"

#include "Components/StaticMeshComponent.h"
#include "Actions/AbyssActionComponent.h"
#include "Animation/AnimInstance.h"

ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = true;

	DoorHallMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("DoorHallMesh");
	DoorHallMeshComp->SetupAttachment(RootComponent);

	DoorMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("DoorMesh");
	DoorMeshComp->SetupAttachment(DoorHallMeshComp);
}