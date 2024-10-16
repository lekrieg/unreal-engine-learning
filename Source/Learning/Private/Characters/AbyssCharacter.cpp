// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AbyssCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Animation/AnimMontage.h"
#include "AbyssInteractionComponent.h"
#include "Animations/ProjectileAttackNotify.h"
#include "Animations/Power1Notify.h"
#include "DrawDebugHelpers.h"
#include "Characters/AbyssAttributeComponent.h"

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

	AttributeComp = CreateDefaultSubobject<UAbyssAttributeComponent>("AttributeComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void AAbyssCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitAnimations();
}

void AAbyssCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComp->OnHealthChanged.AddDynamic(this, &AAbyssCharacter::OnHealthChanged);
}

void AAbyssCharacter::OnHealthChanged(AActor* InstigatorActor, UAbyssAttributeComponent* OwningComp, float NewHealth, float amount)
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
			APlayerController* PC = Cast<APlayerController>(GetController());
			DisableInput(PC);
		}
	}
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
		Input->BindAction(Power1Action, ETriggerEvent::Triggered, this, &AAbyssCharacter::Power1);
		Input->BindAction(Power2Action, ETriggerEvent::Triggered, this, &AAbyssCharacter::Power2);
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
	ProjectileType = EProjectileType::Magic;
	PlayAnimMontage(AttackAnimation);
	
	//GetWorldTimerManager().SetTimer(TimerHandlePrimaryAttack, this, &AAbyssCharacter::PrimaryAttackTimeElapsed, 0.2f);
	//GetWorldTimerManager().ClearTimer(TimerHandlePrimaryAttack);
}

void AAbyssCharacter::ProjectileAttackTimeElapsed()
{
	// TODO: Redo this using instigator and query to ignore the collision with player
	// TODO: Blackhole Projectile - DONE
	// TODO: Dash/Teleport Projectile Ability, should do this in blueprint

	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);

	FVector Start = CameraComp->GetComponentLocation();
	FVector End = Start + (APawn::GetControlRotation().Vector() * 1000);

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

	SpawnParameters.Instigator = this;

	if (ProjectileType == EProjectileType::Magic)
	{
		GetWorld()->SpawnActor<AActor>(PrimaryProjectile, SpawnTransformMatrix, SpawnParameters);
	}
	else if (ProjectileType == EProjectileType::Dash)
	{
		GetWorld()->SpawnActor<AActor>(DashProjectile, SpawnTransformMatrix, SpawnParameters);
	}
}

void AAbyssCharacter::Power1TimeElapsed()
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_PhysicsBody);

	FVector Start = CameraComp->GetComponentLocation();
	FVector End = Start + (APawn::GetControlRotation().Vector() * 1000);

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

	SpawnParameters.Instigator = this;

	GetWorld()->SpawnActor<AActor>(BlackHoleProjectile, SpawnTransformMatrix, SpawnParameters);
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
			UProjectileAttackNotify* ProjectileAttackNotify = Cast<UProjectileAttackNotify>(N.Notify);
			if (ProjectileAttackNotify)
			{
				ProjectileAttackNotify->OnNotified.AddUObject(this, &AAbyssCharacter::ProjectileAttackTimeElapsed);
			}
		}
	}

	if (Power1Animation)
	{
		const TArray<FAnimNotifyEvent> NotifyEvents = Power1Animation->Notifies;
		for (FAnimNotifyEvent N : NotifyEvents)
		{
			UPower1Notify* Power1Notify = Cast<UPower1Notify>(N.Notify);
			if (Power1Notify)
			{
				Power1Notify->OnNotified.AddUObject(this, &AAbyssCharacter::Power1TimeElapsed);
			}
		}
	}
}

void AAbyssCharacter::Jump(const FInputActionValue& InputValue)
{
	ACharacter::Jump();
}

void AAbyssCharacter::Power1()
{
	PlayAnimMontage(Power1Animation);
}

void AAbyssCharacter::Power2()
{
	ProjectileType = EProjectileType::Dash;
	PlayAnimMontage(AttackAnimation);
}
