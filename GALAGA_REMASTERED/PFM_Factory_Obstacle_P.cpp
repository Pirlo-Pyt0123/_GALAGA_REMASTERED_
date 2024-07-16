#include "PFM_Factory_Obstacle_P.h"
#include "H_obstacle_Asteroide.h"
#include "H_Obstacle_Cometa.h"
#include "H_Obstacle_Galactic_Mines.h"
#include "H_Obstacle_Satelite.h"
#include "H_Obstacle_Trufi.h"
#include "H_Obstacle_Station.h"
#include "H_Obstacle_Desechos.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

APFM_Factory_Obstacle_P::APFM_Factory_Obstacle_P()
{
    PrimaryActorTick.bCanEverTick = true;
}

void APFM_Factory_Obstacle_P::BeginPlay()
{
    Super::BeginPlay();
}

void APFM_Factory_Obstacle_P::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

AInteractable_Objects_P* APFM_Factory_Obstacle_P::Create_Interactable_Object(FString Identificador)
{
    FVector MinSpawnLocation = FVector(-400000.0f, -400000.0f, -400000.0f);
    FVector MaxSpawnLocation = FVector(400000.0f, 400000.0f, 400000.0f);
    float MinDistanceBetweenObstacles = 3500.0f; // Ajustar este valor según sea necesario

    FVector SpawnLocation;
    FRotator Rotation = FRotator(0.f, 0.f, 0.f);

    bool bFoundValidLocation = false;
    for (int32 Attempt = 0; Attempt < 1000; ++Attempt)
    {
        SpawnLocation = FVector(
            FMath::RandRange(MinSpawnLocation.X, MaxSpawnLocation.X),
            FMath::RandRange(MinSpawnLocation.Y, MaxSpawnLocation.Y),
            FMath::RandRange(MinSpawnLocation.Z, MaxSpawnLocation.Z)
        );

        bool bIsValidLocation = true;
        for (const FVector& Location : SpawnedLocations)
        {
            if (FVector::Dist(Location, SpawnLocation) < MinDistanceBetweenObstacles)
            {
                bIsValidLocation = false;
                break;
            }
        }

        if (bIsValidLocation)
        {
            bFoundValidLocation = true;
            break;
        }
    }

    if (!bFoundValidLocation)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to find a valid spawn location for obstacle"));
        return nullptr;
    }

    AInteractable_Objects_P* SpawnedObject = nullptr;

    if (Identificador.Equals("Obstacle_Asteroide"))
        SpawnedObject = GetWorld()->SpawnActor<AH_obstacle_Asteroide>(AH_obstacle_Asteroide::StaticClass(), SpawnLocation, Rotation);

    if (Identificador.Equals("Obstacle_Cometa"))
        SpawnedObject = GetWorld()->SpawnActor<AH_Obstacle_Cometa>(AH_Obstacle_Cometa::StaticClass(), SpawnLocation, Rotation);

    if (Identificador.Equals("Obstacle_Galactic_Mines"))
        SpawnedObject = GetWorld()->SpawnActor<AH_Obstacle_Galactic_Mines>(AH_Obstacle_Galactic_Mines::StaticClass(), SpawnLocation, Rotation);

    if (Identificador.Equals("Obstacle_Satelite"))
        SpawnedObject = GetWorld()->SpawnActor<AH_Obstacle_Satelite>(AH_Obstacle_Satelite::StaticClass(), SpawnLocation, Rotation);

    if(Identificador.Equals("Obstacle_Trufi"))
		SpawnedObject = GetWorld()->SpawnActor<AH_Obstacle_Trufi>(AH_Obstacle_Trufi::StaticClass(), SpawnLocation, Rotation);

    if(Identificador.Equals("Obstacle_Station"))
		SpawnedObject = GetWorld()->SpawnActor<AH_Obstacle_Station>(AH_Obstacle_Station::StaticClass(), SpawnLocation, Rotation);

    if(Identificador.Equals("Obstacle_Desechos"))
        SpawnedObject = GetWorld()->SpawnActor<AH_Obstacle_Desechos>(AH_Obstacle_Desechos::StaticClass(), SpawnLocation, Rotation);

    if (SpawnedObject)
    {
        SpawnedLocations.Add(SpawnLocation);
    }

    return SpawnedObject;
}