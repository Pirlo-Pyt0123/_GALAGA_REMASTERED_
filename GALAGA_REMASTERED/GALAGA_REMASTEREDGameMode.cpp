#include "GALAGA_REMASTEREDGameMode.h"
#include "GALAGA_REMASTEREDPawn.h"
#include "Kismet/GameplayStatics.h"
#include "HUD_P_Principal.h"
#include "Z_Ship_Striker.h"
#include "Z_Ship_Bomber.h"
#include "Z_Ship_Vortex.h"
#include "Z_Ship_Tempest.h"
#include "Z_Ship_Specter.h"
#include "Z_Ship_Spark.h"
#include "Z_Ship_Cyclone.h"

AGALAGA_REMASTEREDGameMode::AGALAGA_REMASTEREDGameMode()
{
    // set default pawn class to our character class
    DefaultPawnClass = AGALAGA_REMASTEREDPawn::StaticClass();

    HUDClass = AHUD_P_Principal::StaticClass();
}

void AGALAGA_REMASTEREDGameMode::BeginPlay()
{
    Super::BeginPlay();

}
