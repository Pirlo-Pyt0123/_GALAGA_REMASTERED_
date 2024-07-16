#include "PF_LEVEL_DIFFICULTY_PRIM_B.h"
#include "PF_Level_Difficulty_Easy.h"
#include "PF_Level_Difficulty_Normal.h"
#include "PF_Level_Difficulty_Extreme.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APF_LEVEL_DIFFICULTY_PRIM_B::APF_LEVEL_DIFFICULTY_PRIM_B()
{
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APF_LEVEL_DIFFICULTY_PRIM_B::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void APF_LEVEL_DIFFICULTY_PRIM_B::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APF_LEVEL_DIFFICULTY_PRIM_B::Activation_Mode_Easy()
{
    // Destruye las instancias de dificultades no utilizadas para liberar recursos
    if (Level_Difficulty_Medium) {
        Level_Difficulty_Medium->Destroy();
        Level_Difficulty_Medium = nullptr;
    }
    if (Level_Difficulty_Hard) {
        Level_Difficulty_Hard->Destroy();
        Level_Difficulty_Hard = nullptr;
    }

    // Reutiliza o crea una nueva instancia para la dificultad fácil
    if (!Level_Difficulty_Easy)
    {
        Level_Difficulty_Easy = GetWorld()->SpawnActor<APF_Level_Difficulty_Easy>(APF_Level_Difficulty_Easy::StaticClass());
        if (!Level_Difficulty_Easy) {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to create Level_Difficulty_Easy instance"));
            return;
        }

    }
    //Level_Difficulty_Easy->Setting_Enemy_Ship_Basic();

}

void APF_LEVEL_DIFFICULTY_PRIM_B::Activation_Mode_Normal()
{
    // Destruye las instancias de dificultades no utilizadas
    if (Level_Difficulty_Easy)
    {
        Level_Difficulty_Easy->Destroy();
        Level_Difficulty_Easy = nullptr;
    }
    if (Level_Difficulty_Hard)
    {
        Level_Difficulty_Hard->Destroy();
        Level_Difficulty_Hard = nullptr;
    }

    // Reutiliza o crea una nueva instancia para la dificultad normal
    if (!Level_Difficulty_Medium)
    {
        Level_Difficulty_Medium = GetWorld()->SpawnActor<APF_Level_Difficulty_Normal>(APF_Level_Difficulty_Normal::StaticClass());
        if (!Level_Difficulty_Medium)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to create Level_Difficulty_Medium instance"));
            return;
        }
    }

    //Level_Difficulty_Medium->Setting_Enemy_Ship_Basic();
}

void APF_LEVEL_DIFFICULTY_PRIM_B::Activation_Mode_Extreme()
{
    // Destruye las instancias de dificultades no utilizadas
    if (Level_Difficulty_Easy) {
        Level_Difficulty_Easy->Destroy();
        Level_Difficulty_Easy = nullptr;
    }
    if (Level_Difficulty_Medium) {
        Level_Difficulty_Medium->Destroy();
        Level_Difficulty_Medium = nullptr;
    }

    // Reutiliza o crea una nueva instancia para la dificultad extrema
    if (!Level_Difficulty_Hard)
    {
        Level_Difficulty_Hard = GetWorld()->SpawnActor<APF_Level_Difficulty_Extreme>(APF_Level_Difficulty_Extreme::StaticClass());
        if (!Level_Difficulty_Hard) {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to create Level_Difficulty_Hard instance"));
            return;
        }
    }
    //Level_Difficulty_Hard->Setting_Enemy_Ship_Basic();
}
