// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotEnemy.h"
#include "Engine/World.h"
#include "FPSController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/EngineTypes.h"
#include "DrawDebugHelpers.h"

// Sets default values
ARobotEnemy::ARobotEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARobotEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARobotEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (ScanForPlayer())
	{
		MoveToPlayer(DeltaTime);
	}
}

bool ARobotEnemy::ScanForPlayer()
{
	FHitResult hit;
	FVector myPosition = GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("He is: %s"), *GetWorld()->GetFirstPlayerController()->GetPawn()->GetName());
	FVector playerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FCollisionQueryParams collisionParams;
	collisionParams = FCollisionQueryParams(TEXT(""), false, GetOwner());
	DrawDebugLine(GetWorld(), myPosition, playerPosition, FColor::Green, false, 1.f, 0, 1.f);
	if (GetWorld()->LineTraceSingleByChannel(hit, myPosition, playerPosition, ECollisionChannel::ECC_PhysicsBody, collisionParams))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *hit.GetActor()->GetName()));
		return hit.GetActor()->GetName() == "BP_FPSController_C_0";
	}
	UE_LOG(LogTemp, Warning, TEXT("player not found"));
	return false;
}

void ARobotEnemy::MoveToPlayer(float DeltaTime)
{
	FVector playerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	if (FVector::Dist(GetActorLocation(), playerPosition) > fireDistance)
	{
		UE_LOG(LogTemp, Warning, TEXT("Moving to player"));
		FRotator lookRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), playerPosition);
		lookRotation = FRotator(0.f, lookRotation.Yaw, 0.f);
		SetActorRotation(lookRotation, ETeleportType::None);
		SetActorLocation(GetActorLocation() + GetActorForwardVector() * speed * DeltaTime);
	} else
	{
		if (fireTimer >= fireCooldown)
		{
			UE_LOG(LogTemp, Warning, TEXT("Firing to player"));
			GetWorld()->SpawnActor<ABullet>(bullet);
			fireTimer = 0.f;
		} else
		{
			UE_LOG(LogTemp, Warning, TEXT("Bullet robot cooldown"));
			fireTimer += DeltaTime;
		}
	}
}