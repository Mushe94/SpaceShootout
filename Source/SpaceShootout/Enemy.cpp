// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Engine/World.h"
#include "FPSController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/EngineTypes.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"


// Sets default values
AEnemy::AEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	audioComponent = FindComponentByClass<UAudioComponent>();
	audioComponent->SetSound(runSound);
	player = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (enemyLife > 0 && isPlayerAlive && ScanForPlayer())
	{
		MoveToPlayer(DeltaTime);
	}
}

bool AEnemy::TakeDamage(float damage)
{
	enemyLife -= damage;
	return enemyLife <= 0;
}

bool AEnemy::ScanForPlayer()
{
	FHitResult hit;
	FCollisionQueryParams collisionParams;
	collisionParams.FCollisionQueryParams::AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(hit, spawnPoint->GetComponentLocation(), player->GetActorLocation(), ECollisionChannel::ECC_PhysicsBody, collisionParams))
	{
		return hit.GetActor()->GetName() == "BP_FPSController_C_0";
	}
	return false;
}

void AEnemy::MoveToPlayer(float DeltaTime)
{
	FVector playerPosition = player->GetActorLocation();
	if (FVector::Distance(GetActorLocation(), playerPosition) > fireDistance)
	{
		if (audioComponent)
		{
			if (!audioComponent->IsPlaying())
			{
				audioComponent->Play();
			}
		}
		isMoving = true;
		SetActorLocation(GetActorLocation() + GetActorForwardVector() * movementSpeed * DeltaTime);
	}
	else
	{
		isMoving = false;
		if (audioComponent)
		{
			audioComponent->Stop();
		}
		if (fireTimer >= fireCooldown)
		{
			fireTimer = 0.f;
			ABullet* tempBullet = GetWorld()->SpawnActor<ABullet>(bullet, enemySkeletalMesh->GetSocketLocation("headSocket"), enemySkeletalMesh->GetSocketRotation("headSocket"));
			//tempBullet->AssignOwner(this);
		}
		else
		{
			fireTimer += DeltaTime;
		}
	}
	LookAtPlayer(playerPosition, DeltaTime);
}

void AEnemy::LookAtPlayer(FVector playerPosition, float DeltaTime)
{
	float rotation = (playerPosition - GetActorLocation()).GetSafeNormal().Rotation().Yaw;
	SetActorRotation(FRotator(0.f, rotation, 0.f));
}