// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbyssCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UAbyssAttributeComponent;

class UInputMappingContext;
class UInputAction;
class AAbyssMagicProjectile;
class UAbyssInteractionComponent;
class UAnimMontage;

struct FInputActionValue;

UENUM()
enum class EProjectileType : uint8
{
	Magic UMETA(DisplayName = "Magic"),
	Dash UMETA(DisplayName = "Dash"),
};

UCLASS()
class LEARNING_API AAbyssCharacter : public ACharacter
{
	GENERATED_BODY()

	EProjectileType ProjectileType;

public:
	// Sets default values for this character's properties
	AAbyssCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interact stuff")
	UAbyssInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute")
	UAbyssAttributeComponent* AttributeComp;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* DefaultInputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LookMouseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* PrimaryAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* PrimaryInteractionAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* Power1Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* Power2Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack stuff")
	TSubclassOf<AActor> PrimaryProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Powers stuff")
	TSubclassOf<AActor> BlackHoleProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Powers stuff")
	TSubclassOf<AActor> DashProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation stuff")
	UAnimMontage* AttackAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation stuff")
	UAnimMontage* Power1Animation;

	//FTimerHandle TimerHandlePrimaryAttack;
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UAbyssAttributeComponent* OwningComp, float NewHealth, float amount);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void LookMouse(const FInputActionValue& InputValue);
	void Move(const FInputActionValue& InputValue);
	void PrimaryAttack();
	void ProjectileAttackTimeElapsed();
	void Power1TimeElapsed();
	void PrimaryInteraction();
	void Jump(const FInputActionValue& InputValue);
	void Power1();
	void Power2();
	void InitAnimations();

};
