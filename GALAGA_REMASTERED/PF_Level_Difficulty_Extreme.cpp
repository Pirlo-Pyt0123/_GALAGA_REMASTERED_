// Fill out your copyright notice in the Description page of Project Settings.


#include "PF_Level_Difficulty_Extreme.h"
#include "Z_Enemy_Ship_P.h"
#include "PF_Level_Creator_P.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

APF_Level_Difficulty_Extreme::APF_Level_Difficulty_Extreme()
{
	PrimaryActorTick.bCanEverTick = true;

	Life_Ship_Extreme = 300.0f;
	Speed_Ship_Extreme = 60.0f;
	Shot_Ship_Extreme = 180.0f;

	Life_Obstacle_Extreme = 300.0f;
	Speed_Obstacle_Extreme = 98.0f;
	Damage_Obstacle_Extreme = 150.0f;

	Life_Boss_Extreme = 10000.0f;
	Speed_Boss_Extreme = 1200.0f;
	Shot_Boss_Extreme = 580.0f;

	Life_Boss_Galactus_Extreme = 100000.0f;
	Speed_Boss_Galactus_Extreme = 19500.0f;
	Shot_Boss_Galactus_Extreme = 1350.0f;
}

void APF_Level_Difficulty_Extreme::BeginPlay()
{
	Super::BeginPlay();
	Level_Creator_A = GetWorld()->SpawnActor<APF_Level_Creator_P>(APF_Level_Creator_P::StaticClass());
	Setting_Enemy_Ship_Basic();
	Setting_Obstacles_General();
	Setting_Boss_Ship_Basic();
	Setting_Boss_Galactus();

}

void APF_Level_Difficulty_Extreme::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APF_Level_Difficulty_Extreme::Setting_Enemy_Ship_Basic()
{
	Level_Creator_A->Configure_Ship_N(Life_Ship_Extreme, Speed_Ship_Extreme, Shot_Ship_Extreme);
}

void APF_Level_Difficulty_Extreme::Setting_Obstacles_General()
{
	Level_Creator_A->Configure_Obstacle(Life_Obstacle_Extreme, Speed_Obstacle_Extreme, Damage_Obstacle_Extreme);
}

void APF_Level_Difficulty_Extreme::Setting_Boss_Ship_Basic()
{
	Level_Creator_A->Configure_Boss_Ship(Life_Boss_Extreme, Speed_Boss_Extreme, Shot_Boss_Extreme);
}

void APF_Level_Difficulty_Extreme::Setting_Boss_Galactus()
{
	Level_Creator_A->Configure_Boss_Galactus(Life_Boss_Galactus_Extreme, Speed_Boss_Galactus_Extreme, Shot_Boss_Galactus_Extreme);
}
