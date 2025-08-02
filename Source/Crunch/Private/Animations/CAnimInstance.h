// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

class ACharacter;
class UCharacterMovementComponent;
class UKismetMathLibrary;
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

	 UFUNCTION(BlueprintCallable, meta =(BlueprintThreadSafe))
	 FORCEINLINE float GetSpeed() const { return Speed; }


	 UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	 FORCEINLINE bool IsMoving() const { return Speed != 0; }

	 UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	 FORCEINLINE bool IsNotMoving() const { return Speed == 0; }

	 UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	 FORCEINLINE float GetYawSpeed() const { return YawSpeed; }

	 UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	 FORCEINLINE float GetSmoothedYawSpeed() const { return SmoothedYawSpeed; }
private:
	float Speed;
	float SmoothedYawSpeed;
	float YawSpeed;

	FRotator BodyPrevRot;

	UPROPERTY()
	float YawSpeedSmoothLerpSpeed = 1.f;

	UPROPERTY()
	class ACharacter* OwnerCharacter;

	UPROPERTY()
	class UCharacterMovementComponent* OwnerMovementComp;
};
