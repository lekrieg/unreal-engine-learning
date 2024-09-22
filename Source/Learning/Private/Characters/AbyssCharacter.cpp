// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AbyssCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Animation/AnimMontage.h"
#include "AbyssInteractionComponent.h"
#include "Animations/PrimaryAttackNotify.h"

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

// Called when the game starts or when spawned
void AAbyssCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitAnimations();
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
		Input->BindAction(PrimaryAttackAction, ETriggerEvent::Started, this, &AAbyssCharacter::PrimaryAttack);
		Input->BindAction(PrimaryInteractionAction, ETriggerEvent::Triggered, this, &AAbyssCharacter::PrimaryInteraction);
		Input->BindAction(JumpAction, ETriggerEvent::Started, this, &AAbyssCharacter::Jump);
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
	PlayAnimMontage(AttackAnimation);
	
	//GetWorldTimerManager().SetTimer(TimerHandlePrimaryAttack, this, &AAbyssCharacter::PrimaryAttackTimeElapsed, 0.2f);
	//GetWorldTimerManager().ClearTimer(TimerHandlePrimaryAttack);
}

void AAbyssCharacter::PrimaryAttackTimeElapsed()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, FString::Printf(TEXT("Attack!")));
	}
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	FTransform SpawnTransformMatrix = FTransform(APawn::GetControlRotation(), HandLocation);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	SpawnParameters.Instigator = this;

	GetWorld()->SpawnActor<AActor>(PrimaryProjectile, SpawnTransformMatrix, SpawnParameters);


}

void AAbyssCharacter::PrimaryInteraction()
{
	InteractionComp->PrimaryInteract();
}

void AAbyssCharacter::InitAnimations()
{
	if (AttackAnimation)
	{
		const TArray<FAnimNotifyEvent> NotifyEvents = AttackAnimation->Notifies;
		for (FAnimNotifyEvent N : NotifyEvents)
		{
			UPrimaryAttackNotify* PrimaryAttackNotify = Cast<UPrimaryAttackNotify>(N.Notify);
			if (PrimaryAttackNotify)
			{
				PrimaryAttackNotify->OnNotified.AddUObject(this, &AAbyssCharacter::PrimaryAttackTimeElapsed);
			}
		}
	}
}

void AAbyssCharacter::Jump(const FInputActionValue& InputValue)
{
	ACharacter::Jump();
}
