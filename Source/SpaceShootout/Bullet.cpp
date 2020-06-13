// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/BoxComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	if (isCritical && !propertiesConfigured)
	{
		ConfigureProperties();
	}
}

void ABullet::ConfigureProperties()
{
	damage = criticalDamage;
	UMaterialInterface* material = bulletStaticMesh->GetMaterial(0);
	UMaterialInstanceDynamic* dynamicMaterial = UMaterialInstanceDynamic::Create(material, NULL);
	bulletStaticMesh->SetMaterial(0, dynamicMaterial);
	dynamicMaterial->SetScalarParameterValue(TEXT("Critical"), 1.f);
	propertiesConfigured = true;
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isCritical && bulletStaticMesh && !propertiesConfigured)
	{
		ConfigureProperties();
	}
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * speed * DeltaTime);
}

void ABullet::AssignOwner(AActor* myMaster)
{
	myOwner = myMaster;
}

