// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Engine/World.h"
#include "FPSController.h"
#include "Kismet/KismetMathLibrary.h"
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
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isPlayerAlive && ScanForPlayer())
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
	FVector myPosition = GetActorLocation() + offset;
	FVector playerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FCollisionQueryParams collisionParams;
	collisionParams.FCollisionQueryParams::AddIgnoredActor(this);
	//DrawDebugLine(GetWorld(), myPosition, playerPosition, FColor::Green, false, 1.f, 0, 1.f);
	if (GetWorld()->LineTraceSingleByChannel(hit, myPosition, playerPosition, ECollisionChannel::ECC_PhysicsBody, collisionParams))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *hit.GetActor()->GetName()));
		return hit.GetActor()->GetName() == "BP_FPSController_C_0";
	}
	return false;
}

void AEnemy::MoveToPlayer(float DeltaTime)
{
	FVector playerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	if (FVector::Distance(GetActorLocation(), playerPosition) > fireDistance)
	{
		if (audioComponent)
		{
			if (!audioComponent->IsPlaying())
			{
				audioComponent->SetSound(runSound);
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
			ABullet* tempBullet = GetWorld()->SpawnActor<ABullet>(bullet, GetActorLocation() + offset, GetActorRotation());
			//tempBullet->AssignOwner(GetOwner());
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
	FRotator lookRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), playerPosition);
	lookRotation = FRotator(0.f, lookRotation.Yaw, 0.f);
	lookRotation = UKismetMathLibrary::RLerp(GetActorRotation(), lookRotation, rotationSpeed * DeltaTime, false);
	lookRotation = FRotator(0.f, lookRotation.Yaw, 0.f);
	SetActorRotation(lookRotation, ETeleportType::None);
}