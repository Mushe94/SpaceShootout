// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSController.generated.h"

class UInputComponent;

UCLASS()
class SPACESHOOTOUT_API AFPSController : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void MoveForward(float value);
	void MoveRight(float value);
	void CharacterJump();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
