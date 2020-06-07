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
	startPosition = GetActorLocation();
	isAlive = true;
	weapon = FindComponentByClass<UWeapon>();
	weapon->AssignOwner(GetOwner());
}

// Called every frame
void AFPSController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPSController::Respawn()
{
	SetActorLocation(startPosition);
	currentLife = 100;
	isAlive = true;
}

// Called to bind functionality to input
void AFPSController::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSController::Fire);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSController::CharacterJump);
	PlayerInputComponent->BindAxis("Forward", this, &AFPSController::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &AFPSController::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
}

void AFPSController::UpdatePoints(int points)
{
	currentPoints += points;
}

void AFPSController::TakeDamge(float damage)
{
	currentLife -= damage;
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

void AFPSController::CharacterJump()
{

		Jump();
	
}

void AFPSController::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Dispare"));
	weapon->Fire();
}