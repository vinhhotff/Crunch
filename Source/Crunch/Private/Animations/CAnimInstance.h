// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

class ACharacter;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:	
	 virtual void NativeInitializeAnimation() override;

	 virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	 virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
private:
	UPROPERTY()
	class ACharacter* OwnerCharacter;

	UPROPERTY()
	class UCharacterMovementComponent* OwnerMovementComp;
};
