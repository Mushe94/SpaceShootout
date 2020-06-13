// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SS_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHOOTOUT_API ASS_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
		void EnableEnemies();
	UFUNCTION(BlueprintCallable)
		void DisableEnemies();
	UFUNCTION(BlueprintCallable)
		void RestartLevel();

};
