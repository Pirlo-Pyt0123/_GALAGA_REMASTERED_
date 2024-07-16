// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PF_Level_Difficulty_Base_P.h"
#include "Z_Enemy_Ship_P.h"
#include "PF_Level_Difficulty_Easy.generated.h"


UCLASS()
class GALAGA_REMASTERED_API APF_Level_Difficulty_Easy : public APF_Level_Difficulty_Base_P
{
    GENERATED_BODY()
public:
    APF_Level_Difficulty_Easy();

public:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

public:

    virtual void Setting_Boss_Galactus() override;
    virtual void Setting_Boss_Ship_Basic() override;
    virtual void Setting_Enemy_Ship_Basic() override;
    virtual void Setting_Obstacles_General() override;

public:


    float Life_Ship_Easy;
    float Speed_Ship_Easy;
    float Shot_Ship_Easy;

    float Life_Obstacle_Easy;
    float Speed_Obstacle_Easy;
    float Damage_Obstacle_Easy;

    float Life_Boss_Easy;
    float Speed_Boss_Easy;
    float Shot_Boss_Easy;

    float Life_Boss_Galactus_Easy;
    float Speed_Boss_Galactus_Easy;
    float Shot_Boss_Galactus_Easy;

    UPROPERTY()
    class APF_Level_Creator_P* Level_CreatorE;
};
