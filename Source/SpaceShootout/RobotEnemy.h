// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Bullet.h"
#include "RobotEnemy.generated.h"

UCLASS()
class SPACESHOOTOUT_API ARobotEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARobotEnemy();
	UPROPERTY(EditAnywhere)
		float viewDistance;
	UPROPERTY(EditAnywhere)
		float fireDistance;
	UPROPERTY(EditAnywhere)
		float speed;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABullet> bullet;
	UPROPERTY(EditAnywhere)
		float fireCooldown;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool ScanForPlayer();
	void MoveToPlayer(float DeltaTime);

	float fireTimer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
