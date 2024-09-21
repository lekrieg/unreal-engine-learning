// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AbyssCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "AbyssInteractionComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/GameEngine.h"

// Sets default values
AAbyssCharacter::AAbyssCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<UAbyssInteractionComponent>("InterationComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

// Called every frame
void AAbyssCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAbyssCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	const APlayerController* PC = GetController<APlayerController>();
	const ULocalPlayer* LP = PC->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	Subsystem->ClearAllMappings();

	Subsystem->AddMappingContext(DefaultInputMappingContext, 0);


	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AAbyssCharacter::Jump);
		//Input->BindAction(JumpAction, ETriggerEvent::Completed, this, &AAbyssCharacter::StopJumping);
		
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAbyssCharacter::Move);
		Input->BindAction(LookMouseAction, ETriggerEvent::Triggered, this, &AAbyssCharacter::LookMouse);
		Input->BindAction(PrimaryAttackAction, ETriggerEvent::Triggered, this, &AAbyssCharacter::PrimaryAttack);
		Input->BindAction(PrimaryInteractionAction, ETriggerEvent::Triggered, this, &AAbyssCharacter::PrimaryInteraction);
	}
}

void AAbyssCharacter::LookMouse(const FInputActionValue& InputValue)
{
	const FVector2D Value = InputValue.Get<FVector2D>();

	APawn::AddControllerYawInput(Value.X);
	APawn::AddControllerPitchInput(Value.Y);
}

void AAbyssCharacter::Move(const FInputActionValue& InputValue)
{
	/*const FVector2D AxisValue = InputValue.Get<FVector2D>();
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, FString::Printf(TEXT("Value: %f"), AxisValue.X));
	AddMovementInput(GetActorForwardVector(), AxisValue.X);*/

	FRotator ControlRot = APawn::GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	const FVector2D AxisValue = InputValue.Get<FVector2D>();

	APawn::AddMovementInput(ControlRot.Vector(), AxisValue.Y);

	const FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	APawn::AddMovementInput(RightVector, AxisValue.X);
}

void AAbyssCharacter::PrimaryAttack()
{
	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Attack!"));
	}*/

	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	FTransform SpawnTransformMatrix = FTransform(APawn::GetControlRotation(), HandLocation);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(PrimaryProjectile, SpawnTransformMatrix, SpawnParameters);
}

void AAbyssCharacter::PrimaryInteraction()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Interact!"));
	}

	InteractionComp->PrimaryInteract();
}

//void AAbyssCharacter::Jump(const FInputActionValue& InputValue)
//{
//}
//
//void AAbyssCharacter::StopJump(const FInputActionValue& InputValue)
//{
//}

