// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSController.h"
#include "EnergyShield.generated.h"

UCLASS()
class SPACESHOOTOUT_API AEnergyShield : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnergyShield();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void FollowAndProtectPlayer();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AFPSController* player;
	UPROPERTY(EditAnywhere)
		FVector scaleWhenGrabbed;
	UPROPERTY(EditAnywhere)
		float shieldDuration;

private:
	bool followPlayer;
	float shieldTimer;
};
