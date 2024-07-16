
#include "PF_Level_Creator_P.h"
#include "PB_D_Supreme_Level.h"
#include "PB_Level_Creator.h"
#include "PB_Level_Order.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "PD_World_Changed.h"
#include "PFM_Factory_Obstacle_P.h"
#include "PFM_Factory_Capsule_P.h"
#include "HUD_P_Principal.h"

APF_Level_Creator_P::APF_Level_Creator_P()
{
    PrimaryActorTick.bCanEverTick = true;

    bLevel1Completed = false;
    bLevel2Completed = false;
    bLevel3Completed = false;
    bLevel4Completed = false;
    bLevel5Completed = false;
    bLevel6Completed = false;
    bLevel7Completed = false;
    bLevel8Completed = false;
    bLevel9Completed = false;
    bLevel10Completed = false;
    bLevel11Completed = false;
    bLevel12Completed = false;
    bLevel13Completed = false;
    bLevel14Completed = false;

    Ticked_Entrada = 0;
    Level_Llego = 1;

}

void APF_Level_Creator_P::BeginPlay()
{
    Super::BeginPlay();

    MaterialInstance01 = LoadObject<UMaterialInstance>(nullptr, TEXT("MaterialInstanceConstant'/Game/Space_Creator/Star_Creator/Material_Instances/M_INS_01.M_INS_01'"));
    MaterialInstance02 = LoadObject<UMaterialInstance>(nullptr, TEXT("MaterialInstanceConstant'/Game/Space_Creator/Star_Creator/Material_Instances/M_INS_02.M_INS_02'"));
    MaterialInstance03 = LoadObject<UMaterialInstance>(nullptr, TEXT("MaterialInstanceConstant'/Game/Space_Creator/Star_Creator/Material_Instances/M_INS_03.M_INS_03'"));
    MaterialInstance04 = LoadObject<UMaterialInstance>(nullptr, TEXT("MaterialInstanceConstant'/Game/Space_Creator/Star_Creator/Material_Instances/M_INS_04.M_INS_04'"));
    MaterialInstance05 = LoadObject<UMaterialInstance>(nullptr, TEXT("MaterialInstanceConstant'/Game/Space_Creator/Star_Creator/Material_Instances/M_INS_05.M_INS_05'"));
    MaterialInstance06 = LoadObject<UMaterialInstance>(nullptr, TEXT("MaterialInstanceConstant'/Game/Space_Creator/Star_Creator/Material_Instances/M_INS_06.M_INS_06'"));
    MaterialInstance07 = LoadObject<UMaterialInstance>(nullptr, TEXT("MaterialInstanceConstant'/Game/Space_Creator/Star_Creator/Material_Instances/M_INS_07.M_INS_07'"));

    Level_Order_A = GetWorld()->SpawnActor<APB_Level_Order>(APB_Level_Order::StaticClass());
    if (!Level_Order_A) {

        UE_LOG(LogTemp, Warning, TEXT("Failed to spawn Level Order"));

    }

    Level_Supreme_A = GetWorld()->SpawnActor<APB_D_Supreme_Level>(APB_D_Supreme_Level::StaticClass());
    if (!Level_Supreme_A) 
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to spawn Supreme Level"));
    }
    else {
        Level_Supreme_A->Set_Level_General(Level_Order_A);
        Level_Creator_A = Level_Supreme_A->GET_Level_Creator();
    }

    WorldDecorator = GetWorld()->SpawnActor<APD_World_Changed>(APD_World_Changed::StaticClass());

    HUD = Cast<AHUD_P_Principal>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());


}

void APF_Level_Creator_P::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void APF_Level_Creator_P::Next_Level_PPP()
{
    Level_Llego++;
    CreateLevel(Level_Llego);
}

int32 APF_Level_Creator_P::GetCurrentLevel() const
{
    return Level_Llego;
}

// Implementación de las nuevas funciones para configurar naves y obstáculos
void APF_Level_Creator_P::Configure_Ship_N(float Life, float Speed, float Shot)
{
    Life_Ship_F = Life;
    Speed_Ship_F = Speed;
    Shot_Ship_F = Shot;
    Supreme_Passed_Valores();
}

void APF_Level_Creator_P::Configure_Obstacle(float Life, float Speed, float Damage)
{
    Life_Obstacle_F = Life;
    Speed_Obstacle_F = Speed;
    Damage_Obstacle_F = Damage;
    Supreme_Passed_Valores();
}

void APF_Level_Creator_P::Configure_Boss_Ship(float Life, float Speed, float Shot)
{
    Life_Boss_F = Life;
    Speed_Boss_F = Speed;
    Shot_Boss_F = Shot;
    Supreme_Passed_Valores();
}


void APF_Level_Creator_P::Configure_Boss_Galactus(float Life, float Speed, float Shot)
{
    Life_Boss_Galactus_F = Life;
    Speed_Boss_Galactus_F = Speed;
    Shot_Boss_Galactus_F = Shot;
    Supreme_Passed_Valores();
}


void APF_Level_Creator_P::Supreme_Passed_Valores()
{
    Ticked_Entrada++;

    if (Ticked_Entrada == 4)
    {
        Level_Creator_A->Configuration_Ship_N(Life_Ship_F, Speed_Ship_F, Shot_Ship_F);
        Level_Creator_A->Configuration_Obstacle(Life_Obstacle_F, Speed_Obstacle_F, Damage_Obstacle_F);
        Level_Creator_A->Configuration_Boss(Life_Boss_F, Speed_Boss_F, Shot_Boss_F);
        Level_Creator_A->Configuration_Boss_Galactus(Life_Boss_Galactus_F, Speed_Boss_Galactus_F, Shot_Boss_Galactus_F);
        CreateLevel(Level_Llego);
        Ticked_Entrada = 0;
    }
}

void APF_Level_Creator_P::CreateLevel(int32 Level)
{
    if (!Level_Supreme_A)
    {
        return;
    }

    if (Level == 1 && !bLevel1Completed)
    {
        HUD->ShowLevelScreen("     Level: 1  \n  EXPLORANDO EL UNIVERSO... ");
        HUD->ShowMissionMessage(TEXT(" * Sobrevive las Oleadas Enemigas \n * Encuentra una Terra-Bley"));

        Level_Supreme_A->Level_Construction(Level);
        bLevel1Completed = true;
    }
    else if (Level == 2 && !bLevel2Completed)
    {
        HUD->ShowLevelScreen("     Level: 2  \n  GALAXIA DESCONOCIDA  ");
        HUD->ShowMissionMessage(TEXT(" * Destruye los Asteroides normales \n * Sobrevive!! \n * Encuentra una Terra-Bley"));
        Level_Supreme_A->Level_Construction(Level);
        if (WorldDecorator)
        {
            WorldDecorator->ChangeMaterialInstance(MaterialInstance02);
        }
        bLevel2Completed = true;
    }
    else if (Level == 3 && !bLevel3Completed)
    {

        HUD->ShowLevelScreen("     Level: 3  \n  SUPERVIVENCIA GALACTICA ");
        HUD->ShowMissionMessage(TEXT(" * Destruye a todas las naves \n * Encuentra la Tercera Terra-Bley "));
        Level_Supreme_A->Level_Construction(Level);
        if (WorldDecorator)
        {
            WorldDecorator->ChangeMaterialInstance(MaterialInstance04);
        }
        bLevel3Completed = true;
    }
    else if (Level == 4 && !bLevel4Completed)
    {
        HUD->ShowLevelScreen("     Level: 4  \n  A POR LOS ASTEROIDES PICA-PICA ");
        HUD->ShowMissionMessage(TEXT(" * Prueba los demas Proyectiles \n * Encuentra la Cuarta Terra-Bley "));
        Level_Supreme_A->Level_Construction(Level);
        if (WorldDecorator)
        {
            WorldDecorator->ChangeMaterialInstance(MaterialInstance05);
        }
        bLevel4Completed = true;
    }
    else if (Level == 5 && !bLevel5Completed)
    {
        HUD->ShowLevelScreen("     Level: 5  \n  SUPERANDO LOS OBSTACULOS ESPACIALES ");
        HUD->ShowMissionMessage(TEXT(" * Destruye a las Naves \n * Vence al Jefe \n *Encuentra la quinta Terra-Bley "));
        Level_Supreme_A->Level_Construction(Level);
        if (WorldDecorator)
        {
            WorldDecorator->ChangeMaterialInstance(MaterialInstance06);
        }
        bLevel5Completed = true;
    }
    else if (Level == 6 && !bLevel6Completed)
    {
        HUD->ShowLevelScreen("     Level: 6 \n  GALAXIA ANDROMEDA !!!   ");
        HUD->ShowMissionMessage(TEXT(" * Destruye a las Naves \n * Vence al Jefe \n *Encuentra la sexta Terra-Bley "));
        Level_Supreme_A->Level_Construction(Level);
        if (WorldDecorator)
        {
            WorldDecorator->ChangeMaterialInstance(MaterialInstance02);
        }
        bLevel6Completed = true;
    }
    else if (Level == 7 && !bLevel7Completed)
    {
        HUD->ShowLevelScreen("     Level: 7 \n  EL COMIENZO DE ALGO INESPERADO.... ");
        HUD->ShowMissionMessage(TEXT(" * Destruye asteroides \n * Vence al Jefe \n *Encuentra la septima Terra-Bley "));
        Level_Supreme_A->Level_Construction(Level);
        if (WorldDecorator)
        {
            WorldDecorator->ChangeMaterialInstance(MaterialInstance01);
        }
        bLevel7Completed = true;
    }
    else if (Level == 8 && !bLevel8Completed)
    {
        HUD->ShowLevelScreen("     Level: 8 \n  NEBULOSA DE OSCURIDAD ALTERNA AL MUNDO...? ");
        HUD->ShowMissionMessage(TEXT(" * Destruye a las Naves \n *Encuentra la octava Terra-Bley "));
        Level_Supreme_A->Level_Construction(Level);
        if (WorldDecorator)
        {
            WorldDecorator->ChangeMaterialInstance(MaterialInstance05);
        }
        bLevel8Completed = true;
    }
    else if (Level == 9 && !bLevel9Completed)
    {
        HUD->ShowLevelScreen("     Level: 9 \n ^ ANTIMATERIA ACUMULADA ^");
        HUD->ShowMissionMessage(TEXT(" * Destruye a las Naves \n *Encuentra la novena Terra-Bley "));
        Level_Supreme_A->Level_Construction(Level);
        if (WorldDecorator)
        {
            WorldDecorator->ChangeMaterialInstance(MaterialInstance05);
        }
        bLevel9Completed = true;
    }
    else if (Level == 10 && !bLevel10Completed)
    {
        HUD->ShowLevelScreen("     Level: 10 \n  CINTURON DE ASTEROIDES .... ");
        HUD->ShowMissionMessage(TEXT(" * Destruye a las Naves \n * Vence al Jefe \n *Encuentra la decima Terra-Bley "));
        Level_Supreme_A->Level_Construction(Level);
        if (WorldDecorator)
        {
            WorldDecorator->ChangeMaterialInstance(MaterialInstance03);
        }
        bLevel10Completed = true;
    }
    else if (Level == 11 && !bLevel11Completed)
    {
        HUD->ShowLevelScreen("     Level: 11 \n  El Objetivo Inminente");
        HUD->ShowMissionMessage(TEXT(" * Sobrevive falta poco... \n * Vence al Jefe \n *Encuentra la 11 Terra-Bley "));
        Level_Supreme_A->Level_Construction(Level);
        if (WorldDecorator)
        {
            WorldDecorator->ChangeMaterialInstance(MaterialInstance01);
        }
        bLevel11Completed = true;
    }
    else if (Level == 12 && !bLevel12Completed)
    {
        HUD->ShowLevelScreen("     Level: 12 \n  ANDROMEDA LA NAVE QUE FUE AISLADA DEL AYER ...  ");
        HUD->ShowMissionMessage(TEXT(" * Sigue adelante !!! \n * Vence al Jefe \n *Encuentra la 122 Terra-Bley "));
        Level_Supreme_A->Level_Construction(Level);
        if (WorldDecorator)
        {
            WorldDecorator->ChangeMaterialInstance(MaterialInstance04);
        }
        bLevel12Completed = true;
    }
    else if (Level == 13 && !bLevel13Completed)
    {
        HUD->ShowLevelScreen("     Level: 13 \n  CONTINUEMOS HACIA LA VICTORIA ....  ");
        HUD->ShowMissionMessage(TEXT(" * Preparte para la Mega Galactica \n * Vence al Jefe \n *Encuentra la 13 Terra-Bley "));
        Level_Supreme_A->Level_Construction(Level);
        if (WorldDecorator)
        {
            WorldDecorator->ChangeMaterialInstance(MaterialInstance05);
        }
        bLevel13Completed = true;
    }
    else if (Level == 14 && !bLevel14Completed)
    {
        HUD->ShowLevelScreen("     Level: 14 \n  BATTALLA FINAL - GALACTUS ESTA AQUI !!! ");
        HUD->ShowMissionMessage(TEXT(" * Vence a Galactus .... \n * Gana la Batalla \n * Coronate como el vencedor !!!! "));
        Level_Supreme_A->Level_Construction(Level);
        if (WorldDecorator)
        {
            WorldDecorator->ChangeMaterialInstance(MaterialInstance02);
        }
        bLevel14Completed = true;
    }
    
}
