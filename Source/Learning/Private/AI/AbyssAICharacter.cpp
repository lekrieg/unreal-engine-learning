// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AbyssAICharacter.h"

// Sets default values
AAbyssAICharacter::AAbyssAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAbyssAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAbyssAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

