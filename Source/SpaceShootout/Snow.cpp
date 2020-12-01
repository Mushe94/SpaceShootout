// Fill out your copyright notice in the Description page of Project Settings.


#include "Snow.h"

// Sets default values
ASnow::ASnow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASnow::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASnow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

