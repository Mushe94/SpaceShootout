// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSController.h"
#include "Components/InputComponent.h"

// Sets default values
AFPSController::AFPSController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFPSController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSController::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &AFPSController::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &AFPSController::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
}

void AFPSController::MoveForward(float value)
{
	if (value != 0.f)
	{
		AddMovementInput(GetActorForwardVector(), value);
	}
}

void AFPSController::MoveRight(float value)
{
	if (value != 0.f)
	{
		AddMovementInput(GetActorRightVector(), value);
	}
}