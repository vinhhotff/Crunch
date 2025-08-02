// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/CPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>

ACPlayerCharacter::ACPlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	CameraBoom->SetupAttachment(GetRootComponent());

	ViewCam = CreateDefaultSubobject<UCameraComponent>("View Cam");
	ViewCam->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 720.f, 0.f);
}

void ACPlayerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	APlayerController* PC = GetController<APlayerController>();
	if (PC)
	{
		auto* InputSubsystem = PC->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if (InputSubsystem)
		{
			InputSubsystem->RemoveMappingContext(GameplayInputMappingContext);
			InputSubsystem->AddMappingContext(GameplayInputMappingContext, 0);
		}
	}
}

void ACPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInput)
	{
		EnhancedInput->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::Jump);
		EnhancedInput->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::HandleLookInput);
		EnhancedInput->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::HandleMoveInput);
	}
}

void ACPlayerCharacter::HandleLookInput(const FInputActionValue& InputActionValue)
{
	FVector2D InputVal = InputActionValue.Get<FVector2D>();
	float LookSensitivity = 0.5f;

	AddControllerPitchInput(InputVal.Y*-1.0f * LookSensitivity);
	AddControllerYawInput(InputVal.X * LookSensitivity);
}

void ACPlayerCharacter::HandleMoveInput(const FInputActionValue& InputActionValue)
{
	FVector2D InputVal = InputActionValue.Get<FVector2D>();

	if (!InputVal.IsNearlyZero())
	{
		InputVal.Normalize();

		// Di chuyển theo hướng camera (hoặc controller)
		const FVector ForwardDir = GetMoveFwdDir();
		const FVector RightDir = GetLookRightDir();

		AddMovementInput(ForwardDir, InputVal.Y);
		AddMovementInput(RightDir, InputVal.X);
	}
}

FVector ACPlayerCharacter::GetLookRightDir() const
{
	return ViewCam->GetRightVector().GetSafeNormal2D();
}

FVector ACPlayerCharacter::GetLookFwdDir() const
{
	return ViewCam->GetForwardVector().GetSafeNormal2D();
}

FVector ACPlayerCharacter::GetMoveFwdDir() const
{
	// Dùng hướng nhìn của controller để tính forward vector (phổ biến hơn camera)
	const FRotator YawRotation(0, GetControlRotation().Yaw, 0);
	return FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
}
