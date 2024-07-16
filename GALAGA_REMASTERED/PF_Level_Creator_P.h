#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PF_Level_Creator_P.generated.h"

UCLASS()
class GALAGA_REMASTERED_API APF_Level_Creator_P : public AActor
{
    GENERATED_BODY()

public:
    APF_Level_Creator_P();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    void CreateLevel(int32 Level);
    void Next_Level_PPP();


    //void Get_Passed_Ship();

    void Supreme_Passed_Valores();


    // Nuevas funciones para configurar naves y obstáculos
    void Configure_Ship_N(float Life, float Speed, float Shot);

    void Configure_Boss_Ship(float Life, float Speed, float Shot);

    void Configure_Obstacle(float Life, float Speed, float Damage);

    void Configure_Boss_Galactus(float Life, float Speed, float Shot);



private:
    UPROPERTY()
    class APB_D_Supreme_Level* Level_Supreme_A;

    UPROPERTY()
    class APB_Level_Order* Level_Order_A;

    UPROPERTY()
    class APB_Level_Creator* Level_Creator_A;

    UPROPERTY()
    FString MapName;

    bool bLevel1Completed;
    bool bLevel2Completed;
    bool bLevel3Completed;
    bool bLevel4Completed;
    bool bLevel5Completed;
    bool bLevel6Completed;
    bool bLevel7Completed;
    bool bLevel8Completed;
    bool bLevel9Completed;
    bool bLevel10Completed;
    bool bLevel11Completed;
    bool bLevel12Completed;
    bool bLevel13Completed;
    bool bLevel14Completed;

    int32 Level_Llego;


    UPROPERTY()
    class APD_World_Changed* WorldDecorator;

    UPROPERTY()
    class UMaterialInstance* MaterialInstance01;

    UPROPERTY()
    class UMaterialInstance* MaterialInstance02;

    UPROPERTY()
    class UMaterialInstance* MaterialInstance03;

    UPROPERTY()
    class UMaterialInstance* MaterialInstance04;

    UPROPERTY()
    class UMaterialInstance* MaterialInstance05;

    UPROPERTY()
    class UMaterialInstance* MaterialInstance06;

    UPROPERTY()
    class UMaterialInstance* MaterialInstance07;

    // Método para obtener el nivel actual
    UFUNCTION(BlueprintCallable, Category = "Level")
    int32 GetCurrentLevel() const;

    //Crear variables para recibir la configuración de las naves y obstáculos
    float Life_Ship_F;
    float Speed_Ship_F;
    float Shot_Ship_F;

    float Life_Obstacle_F;
    float Speed_Obstacle_F;
    float Damage_Obstacle_F;

    float Life_Boss_F;
    float Speed_Boss_F;
    float Shot_Boss_F;

    float Life_Boss_Galactus_F;
    float Speed_Boss_Galactus_F;
    float Shot_Boss_Galactus_F;

    class AHUD_P_Principal* HUD;


    int32 Ticked_Entrada;

};
