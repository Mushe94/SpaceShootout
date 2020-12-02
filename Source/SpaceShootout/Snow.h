// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSController.h"
#include "Snow.generated.h"

UCLASS()
class SPACESHOOTOUT_API ASnow : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float slowDuration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float slowMovementSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AFPSController* player;
};
