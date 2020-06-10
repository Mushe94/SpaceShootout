// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Engine/World.h"
#include "Components/ActorComponent.h"
#include "Bullet.h"
#include "Weapon.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SPACESHOOTOUT_API UWeapon : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeapon();
	void Fire();

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABullet> bullet;
	UPROPERTY(EditAnywhere)
		float fireCooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool fireEffect;
	UPROPERTY(EditAnywhere)
		FVector offset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* skeletalMesh;
	UPROPERTY(EditAnywhere)
		float criticalChance;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	AActor* myOwner;
	float fireTimer;
	bool fired;
	UMaterialInstanceDynamic* dynamicMaterial;
	bool isNextFireCritical;
	bool materialCreated;
	void CreateNewMaterial();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void AssignOwner(AActor* myHolder);
};
