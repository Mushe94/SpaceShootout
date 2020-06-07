// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Weapon.h"
#include "GameFramework/Character.h"
#include "Entity.h"
#include "FPSController.generated.h"

class UInputComponent;

UCLASS()
class SPACESHOOTOUT_API AFPSController : public ACharacter, public IEntity
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float currentLife;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int currentPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isAlive;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
		FVector startPosition;

	void MoveForward(float value);
	void MoveRight(float value);
	void CharacterJump();
	void Fire();

	UWeapon* weapon;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
		void TakeDamge(float damage);
	UFUNCTION(BlueprintCallable)
		void UpdatePoints(int points);
	UFUNCTION(BlueprintCallable)
		void Respawn();
};
