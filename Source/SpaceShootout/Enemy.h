// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Bullet.h"
#include "GameFramework/Actor.h"
#include "Entity.h"
#include "Enemy.generated.h"

UCLASS()
class SPACESHOOTOUT_API AEnemy : public AActor, public IEntity
{
	GENERATED_BODY()

public:
	AEnemy();
	virtual void Tick(float DeltaTime) override;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float enemyLife;
	UPROPERTY(BlueprintReadWrite)
		bool isPlayerAlive;
	UPROPERTY(BlueprintReadWrite)
		bool isMoving;
	UPROPERTY()
		UAudioComponent* audioComponent;
	UPROPERTY(EditAnywhere)
		USoundCue* runSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* spawnPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* enemySkeletalMesh;
	UFUNCTION(BlueprintCallable)
		bool TakeDamage(float damage);

protected:
	virtual void BeginPlay() override;

private:
	AActor* player;
	bool ScanForPlayer();
	void MoveToPlayer(float DeltaTime);
	void LookAtPlayer(FVector playerPosition, float DeltaTime);
	float fireTimer;
};
