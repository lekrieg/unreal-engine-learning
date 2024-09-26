// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Delegates/DelegateCombinations.h"
#include "Power1Notify.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNotifiedSignature);

/**
 * 
 */
UCLASS()
class LEARNING_API UPower1Notify : public UAnimNotify
{
	GENERATED_BODY()
	
public:

	FOnNotifiedSignature OnNotified;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
