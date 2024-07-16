#include "PF_Level_Difficulty_Normal.h"
#include "Z_Enemy_Ship_P.h"
#include "PF_Level_Creator_P.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"



APF_Level_Difficulty_Normal::APF_Level_Difficulty_Normal()
{
    PrimaryActorTick.bCanEverTick = true;

    Life_Ship_Normal = 200.0f;
    Speed_Ship_Normal = 50.0f;
    Shot_Ship_Normal = 59.0f;

    Life_Obstacle_Normal = 60.0f;
    Speed_Obstacle_Normal = 13.0f;
    Damage_Obstacle_Normal = 50.0f;

    Life_Boss_Normal = 18000.0f;
    Speed_Boss_Normal = 850.0f;
    Shot_Boss_Normal = 400.0f;


    Life_Boss_Galactus_Normal = 100000.0f;
    Speed_Boss_Galactus_Normal = 1300.0f;
    Shot_Boss_Galactus_Normal = 600.0f;
}

void APF_Level_Difficulty_Normal::BeginPlay()
{
    Super::BeginPlay();
    
    Level_Creator_N = GetWorld()->SpawnActor<APF_Level_Creator_P>(APF_Level_Creator_P::StaticClass());
    Setting_Enemy_Ship_Basic();
    Setting_Obstacles_General();
    Setting_Boss_Ship_Basic();
    Setting_Boss_Galactus();
}

void APF_Level_Difficulty_Normal::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APF_Level_Difficulty_Normal::Setting_Enemy_Ship_Basic()
{
    Level_Creator_N->Configure_Ship_N(Life_Ship_Normal, Speed_Ship_Normal, Shot_Ship_Normal);

}

void APF_Level_Difficulty_Normal::Setting_Obstacles_General()
{
    Level_Creator_N->Configure_Obstacle(Life_Obstacle_Normal, Speed_Obstacle_Normal, Damage_Obstacle_Normal);
}

void APF_Level_Difficulty_Normal::Setting_Boss_Ship_Basic()
{
    Level_Creator_N->Configure_Boss_Ship(Life_Boss_Normal, Speed_Boss_Normal, Shot_Boss_Normal);
}


void APF_Level_Difficulty_Normal::Setting_Boss_Galactus()
{
    Level_Creator_N->Configure_Boss_Galactus(Life_Boss_Galactus_Normal, Speed_Boss_Galactus_Normal, Shot_Boss_Galactus_Normal);
}


