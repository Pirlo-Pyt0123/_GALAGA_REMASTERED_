// Fill out your copyright notice in the Description page of Project Settings.

#include "PF_Level_Difficulty_Easy.h"
#include "Z_Enemy_Ship_P.h"
#include "PB_D_Supreme_Level.h"
#include "PF_Level_Creator_P.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


APF_Level_Difficulty_Easy::APF_Level_Difficulty_Easy()
{
    PrimaryActorTick.bCanEverTick = true;

    Life_Ship_Easy = 150.0f;
    Speed_Ship_Easy = 40.0f;
    Shot_Ship_Easy = 20.0f;

    Life_Obstacle_Easy = 140.0f;
    Speed_Obstacle_Easy = 30.0f;
    Damage_Obstacle_Easy = 30.0f;

    Life_Boss_Easy = 30000.0f;
    Speed_Boss_Easy = 750.0f;
    Shot_Boss_Easy = 350.0f;

    Life_Boss_Galactus_Easy = 100000.0f;
    Speed_Boss_Galactus_Easy = 1100.0f;
    Shot_Boss_Galactus_Easy = 500.0f;
}

void APF_Level_Difficulty_Easy::BeginPlay()
{
    Super::BeginPlay();

    Level_CreatorE = GetWorld()->SpawnActor<APF_Level_Creator_P>(APF_Level_Creator_P::StaticClass());
    Setting_Enemy_Ship_Basic();
    Setting_Boss_Ship_Basic();
    Setting_Obstacles_General();
    Setting_Boss_Galactus();
}


void APF_Level_Difficulty_Easy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APF_Level_Difficulty_Easy::Setting_Enemy_Ship_Basic()
{
    Level_CreatorE->Configure_Ship_N(Life_Ship_Easy, Speed_Ship_Easy, Shot_Ship_Easy);
}

void APF_Level_Difficulty_Easy::Setting_Obstacles_General()
{
    Level_CreatorE->Configure_Obstacle(Life_Obstacle_Easy, Speed_Obstacle_Easy, Damage_Obstacle_Easy);
}

void APF_Level_Difficulty_Easy::Setting_Boss_Ship_Basic()
{
    Level_CreatorE->Configure_Boss_Ship(Life_Boss_Easy, Speed_Boss_Easy, Shot_Boss_Easy);
}

void APF_Level_Difficulty_Easy::Setting_Boss_Galactus()
{
    Level_CreatorE->Configure_Boss_Galactus(Life_Boss_Galactus_Easy, Speed_Boss_Galactus_Easy, Shot_Boss_Galactus_Easy);
}
