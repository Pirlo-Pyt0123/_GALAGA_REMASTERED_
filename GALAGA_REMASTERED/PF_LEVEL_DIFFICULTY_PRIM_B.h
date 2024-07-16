#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PF_LEVEL_DIFFICULTY_PRIM_B.generated.h"

UCLASS()
class GALAGA_REMASTERED_API APF_LEVEL_DIFFICULTY_PRIM_B : public AActor
{
    GENERATED_BODY()

public:
    APF_LEVEL_DIFFICULTY_PRIM_B();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    void Activation_Mode_Easy();
    void Activation_Mode_Normal();
    void Activation_Mode_Extreme();

private:
    UPROPERTY()
    class APF_Level_Difficulty_Easy* Level_Difficulty_Easy;

    UPROPERTY()
    class APF_Level_Difficulty_Normal* Level_Difficulty_Medium;

    UPROPERTY()
    class APF_Level_Difficulty_Extreme* Level_Difficulty_Hard;
};
