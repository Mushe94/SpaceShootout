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
	startingLife = currentLife;
	startPosition = GetActorLocation();
	isAlive = true;
	weapon = FindComponentByClass<UWeapon>();
	audioComponent = FindComponentByClass<UAudioComponent>();
}

// Called every frame
void AFPSController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPSController::Respawn()
{
	SetActorLocation(startPosition);
	currentLife = startingLife;
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

bool AFPSController::TakeDamage(float damage)
{
	currentLife -= damage;
	return currentLife <= 0;
}

void AFPSController::MoveForward(float value)
{
	if (currentLife > 0)
	{
		if (value != 0.f)
		{
			if (audioComponent)
			{
				if (!audioComponent->IsPlaying())
				{
					if (audioComponent->Sound != runSound)
					{
						audioComponent->SetSound(runSound);
					}
					audioComponent->Play();
				}
			}
			isGoingForwards = true;
			AddMovementInput(GetActorForwardVector(), value);
		}
		else
		{
			isGoingForwards = false;
			if (!isGoingForwards && !isGoingSideways)
			{
				audioComponent->Stop();
			}
		}
	}
}

void AFPSController::MoveRight(float value)
{
	if (currentLife > 0)
	{
		if (value != 0.f)
		{
			if (audioComponent)
			{
				if (!audioComponent->IsPlaying())
				{
					if (audioComponent->Sound != runSound)
					{
						audioComponent->SetSound(runSound);
					}
					audioComponent->Play();
				}
			}
			isGoingSideways = true;
			AddMovementInput(GetActorRightVector(), value);
		}
		else
		{
			isGoingSideways = false;
			if (!isGoingForwards && !isGoingSideways)
			{
				audioComponent->Stop();
			}
		}
	}
}

void AFPSController::CharacterJump()
{
	if (currentLife > 0)
	{
		Jump();
	}
}

void AFPSController::Fire()
{
	if (currentLife > 0)
	{
		weapon->Fire();
	}
}