// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergyShield.h"
#include "Engine/World.h"

// Sets default values
AEnergyShield::AEnergyShield()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnergyShield::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnergyShield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (followPlayer)
	{
		SetActorLocation(player->GetActorLocation());
		shieldTimer += DeltaTime;
		if (shieldTimer >= shieldDuration)
		{
			player->isImmortal = false;
			Destroy();
		}
	}
}

void AEnergyShield::FollowAndProtectPlayer()
{
	followPlayer = true;
	player->isImmortal = true;
	SetActorScale3D(scaleWhenGrabbed);
}

