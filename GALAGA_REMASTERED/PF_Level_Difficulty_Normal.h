#pragma once

#include "CoreMinimal.h"
#include "PF_Level_Difficulty_Base_P.h"
#include "PF_Level_Difficulty_Normal.generated.h"

UCLASS()
class GALAGA_REMASTERED_API APF_Level_Difficulty_Normal : public APF_Level_Difficulty_Base_P
{
    GENERATED_BODY()

public:

    APF_Level_Difficulty_Normal();


public:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;


public:

    virtual void Setting_Boss_Galactus() override;
    virtual void Setting_Boss_Ship_Basic() override;
    virtual void Setting_Enemy_Ship_Basic() override;
    virtual void Setting_Obstacles_General() override;

public:
    float Life_Ship_Normal;
    float Speed_Ship_Normal;
    float Shot_Ship_Normal;

    float Life_Obstacle_Normal;
    float Speed_Obstacle_Normal;
    float Damage_Obstacle_Normal;

    float Life_Boss_Normal;
    float Speed_Boss_Normal;
    float Shot_Boss_Normal;

    float Life_Boss_Galactus_Normal;
    float Speed_Boss_Galactus_Normal;
    float Shot_Boss_Galactus_Normal;

    UPROPERTY()
    class APF_Level_Creator_P* Level_Creator_N;

};
