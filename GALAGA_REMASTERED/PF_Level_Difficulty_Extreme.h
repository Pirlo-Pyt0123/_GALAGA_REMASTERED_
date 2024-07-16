// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PF_Level_Difficulty_Base_P.h"
#include "PF_Level_Difficulty_Extreme.generated.h"


UCLASS()
class GALAGA_REMASTERED_API APF_Level_Difficulty_Extreme : public APF_Level_Difficulty_Base_P
{
    GENERATED_BODY()

public:

    APF_Level_Difficulty_Extreme();

public:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

public:

    virtual void Setting_Boss_Galactus() override;
    virtual void Setting_Boss_Ship_Basic() override;
    virtual void Setting_Enemy_Ship_Basic() override;
    virtual void Setting_Obstacles_General() override;

public:


    float Life_Ship_Extreme;
    float Speed_Ship_Extreme;
    float Shot_Ship_Extreme;

    float Life_Obstacle_Extreme;
    float Speed_Obstacle_Extreme;
    float Damage_Obstacle_Extreme;
    
    float Life_Boss_Extreme;
    float Speed_Boss_Extreme;
    float Shot_Boss_Extreme;

    float Life_Boss_Galactus_Extreme;
    float Speed_Boss_Galactus_Extreme;
    float Shot_Boss_Galactus_Extreme;

    UPROPERTY()
    class APF_Level_Creator_P* Level_Creator_A;
};
