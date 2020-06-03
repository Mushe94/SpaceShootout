// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Bullet.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class SPACESHOOTOUT_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();
	UPROPERTY(EditAnywhere)
		float viewDistance;
	UPROPERTY(EditAnywhere)
		float fireDistance;
	UPROPERTY(EditAnywhere)
		float movementSpeed;
	UPROPERTY(EditAnywhere)
		float rotationSpeed;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABullet> bullet;
	UPROPERTY(EditAnywhere)
		float fireCooldown;
	UPROPERTY(EditAnywhere)
		FVector offset;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool ScanForPlayer();
	void MoveToPlayer(float DeltaTime);
	void LookAtPlayer(FVector playerPosition, float DeltaTime);

	float fireTimer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
