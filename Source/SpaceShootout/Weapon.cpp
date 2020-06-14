// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/InputComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInterface.h"

// Sets default values for this component's properties
UWeapon::UWeapon()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeapon::BeginPlay()
{
	Super::BeginPlay();
	myOwner = GetOwner();
	fireCooldown = 0.1f;
	criticalChance = 0.1f;
	if (skeletalMesh)
	{
		CreateNewMaterial();
	}
}

void UWeapon::CreateNewMaterial()
{
	UMaterialInterface* material = skeletalMesh->GetMaterial(0);
	dynamicMaterial = UMaterialInstanceDynamic::Create(material, NULL);
	skeletalMesh->SetMaterial(0, dynamicMaterial);
	materialCreated = true;
}

// Called every frame
void UWeapon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (!materialCreated && skeletalMesh)
	{
		CreateNewMaterial();
	}

	if (fireTimer < fireCooldown)
	{
		fireTimer += DeltaTime;
	}
}

void UWeapon::Fire()
{
	if (fireTimer >= fireCooldown)
	{
		fireEffect = true;
		fireTimer = 0.f;
		FActorSpawnParameters params;
		params.Owner = myOwner;
		ABullet* tempBullet = GetWorld()->SpawnActor<ABullet>(bullet, spawnPoint->GetComponentLocation(), spawnPoint->GetComponentRotation(), params);
		if (isNextFireCritical)
		{
			tempBullet->isCritical = true;
		}
		if (FMath::RandRange(0.f, 1.f) < criticalChance)
		{
			isNextFireCritical = true;
			dynamicMaterial->SetScalarParameterValue(TEXT("Critical"), 1.f);
		}
		else
		{
			isNextFireCritical = false;
			dynamicMaterial->SetScalarParameterValue(TEXT("Critical"), 0.f);
		}
	}
}

void UWeapon::AssignOwner(AActor* myHolder)
{
	myOwner = myHolder;
}