// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Enemy.h"

void ASS_GameModeBase::EnableEnemies()
{
	TArray<AActor*> enemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), enemies);
	for (size_t i = 0; i < enemies.Num(); i++)
	{
		Cast<AEnemy>(enemies[i])->isPlayerAlive = true;
	}
}

void ASS_GameModeBase::DisableEnemies()
{
	TArray<AActor*> enemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), enemies);
	for (size_t i = 0; i < enemies.Num(); i++)
	{
		Cast<AEnemy>(enemies[i])->isPlayerAlive = false;
	}
}

void ASS_GameModeBase::RestartLevel()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}