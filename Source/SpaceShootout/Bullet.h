// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class SPACESHOOTOUT_API ABullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABullet();
	UPROPERTY(EditAnywhere)
		float speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float damage;
	UPROPERTY(EditAnywhere)
		float criticalDamage;
	UPROPERTY(BlueprintReadWrite)
		AActor* myOwner;
	UPROPERTY()
		bool isCritical;
	UPROPERTY(BlueprintReadWrite)
		UStaticMeshComponent* bulletStaticMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void AssignOwner(AActor* myMaster);

private:
	bool propertiesConfigured;
	void ConfigureProperties();
};
